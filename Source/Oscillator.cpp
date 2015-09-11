#include "Oscillator.h"

Oscillator::Oscillator() : phase(0.0),
                           phaseDelta(0.0),
                           prevOut(0.0),
                           sampleRate(44100.0)
{
    waveform = Waveform::SINE;
}

Oscillator::Oscillator(Waveform waveform) : phase(0.0),
                                            phaseDelta(0.0),
                                            prevOut(0.0),
                                            sampleRate(44100.0)
{
    this->waveform = waveform;
}

// http://www.martin-finke.de/blog/articles/audio-plugins-018-polyblep-oscillator/
double Oscillator::polyBlep(double t) {
    double dt = phaseDelta / (2 * double_Pi);
    if(t < dt) {
        t /= dt;
        return t+t - t*t - 1.0;
    } else if(t > 1.0 - dt) {
        t =(t - 1.0) / dt;
        return t*t + t+t + 1.0;
    } else return 0.0;
}

double Oscillator::naiveWaveform(Waveform waveform) {
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

float Oscillator::getSample()
{
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
    
    phase += phaseDelta;

    while(phase >= 2 * double_Pi) {
        phase -= 2 * double_Pi;
    }
    
    return value;
}

void Oscillator::setFreq(double freq, double sampleRate)
{
    this->phaseDelta = freq * 2 * double_Pi / sampleRate;
}
