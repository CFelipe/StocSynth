#include "Oscillator.h"

OscillatorVoice::OscillatorVoice() : phaseDelta(0.0),
                                     tailOff(0.0),
                                     prevOut(0.0)
{
    waveform = Waveform::SINE;
    distribution = std::normal_distribution<double>(0.0, 5.0);
}

OscillatorVoice::OscillatorVoice(Waveform waveform) : phaseDelta(0.0),
                                                      tailOff(0.0),
                                                      prevOut(0.0)
{
    this->waveform = waveform;
    distribution = std::normal_distribution<double>(0.0, 5.0);
}

// http://www.martin-finke.de/blog/articles/audio-plugins-018-polyblep-oscillator/
double OscillatorVoice::polyBlep(double t) {
    double dt = phaseDelta / (2 * double_Pi);
    if(t < dt) {
        t /= dt;
        return t+t - t*t - 1.0;
    } else if(t > 1.0 - dt) {
        t =(t - 1.0) / dt;
        return t*t + t+t + 1.0;
    } else return 0.0;
}

double OscillatorVoice::naiveWaveform(Waveform waveform) {
    double value;
    switch (waveform) {
        case Waveform::SINE:
            value = sin(phase);
            break;
        case Waveform::SQUARE:
            if (phase < double_Pi) {
                value = 1.0;
            } else {
                value = -1.0;
            }
            break;
        case Waveform::SAW:
            value = (2.0 * phase / double_Pi * 2) - 1.0;
            break;
        case Waveform::TRIANGLE:
            value = -1.0 + (2.0 * phase / double_Pi * 2);
            value = 2.0 * (fabs(value) - 0.5);
            break;
        default:
            break;
    }
    return value;
}


bool OscillatorVoice::canPlaySound(SynthesiserSound* sound) {
    return dynamic_cast<OscillatorSound*>(sound) != nullptr;
}

void OscillatorVoice::startNote(int midiNoteNumber, float velocity,
                               SynthesiserSound* /*sound*/,
                               int /*currentPitchWheelPosition*/) {
    level = velocity * 0.015;

    double freq = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    phaseDelta = freq * 2 * double_Pi / getSampleRate();
    phase = 0.0;
    
    envelope.enterStage(Envelope::ENVELOPE_STAGE_ATTACK);
}

void OscillatorVoice::stopNote(float /*velocity*/, bool allowTailOff) {
    envelope.enterStage(Envelope::ENVELOPE_STAGE_RELEASE);
}

void OscillatorVoice::changeWaveform(Waveform waveform) {
    this->waveform = waveform;
}

void OscillatorVoice::renderNextBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples)
{
    while(--numSamples >= 0) {
        const float realLevel = ((tailOff > 0) ? (level * tailOff) : level);

        double value = 0.0;

        double t = phase / (2 * double_Pi);

        value = naiveWaveform(waveform);

        if(waveform == Waveform::SAW) {
            value -= polyBlep(t);
        } else if(waveform == Waveform::SQUARE) {
            value += polyBlep(t);
            value -= polyBlep(fmod(t + 0.5, 1.0));
        } else if(waveform == Waveform::TRIANGLE) {
            value = phaseDelta * value + (1 - phaseDelta) * prevOut;
            prevOut = value;
        }

        const float currentSample = value * realLevel * envelope.nextSample();

        for(int i = outputBuffer.getNumChannels(); --i >= 0;)
            outputBuffer.addSample(i, startSample, currentSample);

        phase += phaseDelta;

        while(phase >= 2 * double_Pi) {
            phase -= 2 * double_Pi;
        }

        ++startSample;

        if(tailOff > 0) {
            tailOff *= 0.99;

            if(tailOff <= 0.005) {
                clearCurrentNote();

                phaseDelta = 0.0;
                break;
            }
        }
    }
}
