#include "SynthVoice.h"

SynthVoice::SynthVoice() : level(0.0),
                           tailOff(0.0),
                           prevOut(0.0)
{
    distribution = std::normal_distribution<double>(0.0, 10.0);
}

bool SynthVoice::canPlaySound(SynthesiserSound* sound) {
    return dynamic_cast<SynthSound*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity,
                                SynthesiserSound* /*sound*/,
                                int /*currentPitchWheelPosition*/) {
    level = velocity * 0.015;
    
    double freq = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    
    for(int i = 0; i < 10; i++) {
        osc[i].setFreq(freq * i + 1, getSampleRate());
        randomAmps[i] = fabs(distribution(generator) / 4);
    }
    
    envelope.enterStage(Envelope::ENVELOPE_STAGE_ATTACK);
}

void SynthVoice::stopNote(float /*velocity*/, bool allowTailOff) {
    envelope.enterStage(Envelope::ENVELOPE_STAGE_RELEASE);
}

void SynthVoice::changeCutoff(float cutoff) {
    filter.setCutoff(cutoff);
}

void SynthVoice::changeRes(float res) {
    filter.setResonance(res);
}

void SynthVoice::changeAmpA(float a) {
    envelope.setStageValue(Envelope::EnvelopeStage::ENVELOPE_STAGE_ATTACK, a);
}

void SynthVoice::changeAmpD(float d) {
    envelope.setStageValue(Envelope::EnvelopeStage::ENVELOPE_STAGE_DECAY, d);
}

void SynthVoice::changeAmpS(float s) {
    envelope.setStageValue(Envelope::EnvelopeStage::ENVELOPE_STAGE_SUSTAIN, s);
}

void SynthVoice::changeAmpR(float r) {
    envelope.setStageValue(Envelope::EnvelopeStage::ENVELOPE_STAGE_RELEASE, r);
}

Envelope SynthVoice::getEnvelope() {
    return envelope;
}

void SynthVoice::renderNextBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples)
{
    while(--numSamples >= 0) {
        const float realLevel = ((tailOff > 0) ? (level * tailOff) : level);
        
        double value = 0;
        for(int i = 0; i < 10; i++) {
            value += osc[i].getSample();// * randomAmps[i];
        }
        
        double envelopeSample = envelope.nextSample();
        float currentSample = value * realLevel * envelopeSample;
        currentSample = filter.nextSample(currentSample);
        
        if(envelopeSample == 0.0)
            clearCurrentNote();
        
        for(int i = outputBuffer.getNumChannels(); --i >= 0;)
            outputBuffer.addSample(i, startSample, currentSample);
        
        ++startSample;
    }

}
