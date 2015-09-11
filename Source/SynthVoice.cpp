#include "SynthVoice.h"

SynthVoice::SynthVoice() : level(0.0),
                           tailOff(0.0),
                           prevOut(0.0)
{
    var135Distribution = std::normal_distribution<double>(0.0, 0.3f);
    var246Distribution = std::normal_distribution<double>(0.0, 0.3f);
    var789Distribution = std::normal_distribution<double>(0.0, 0.3f);
    pitch135Distribution = std::normal_distribution<double>(0.0, 0.3f);
    pitch246Distribution = std::normal_distribution<double>(0.0, 0.3f);
    pitch789Distribution = std::normal_distribution<double>(0.0, 0.3f);
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
        osc[i].setFreq(freq * (i + 1), getSampleRate());
    }
    
    osc[10].setFreq(freq / 2, getSampleRate());
    
    envelope.enterStage(Envelope::ENVELOPE_STAGE_ATTACK);
}

void SynthVoice::stopNote(float /*velocity*/, bool allowTailOff) {
    envelope.enterStage(Envelope::ENVELOPE_STAGE_RELEASE);
}

void SynthVoice::changeToneAmp(float toneAmp) {
    this->toneAmp = toneAmp;
}

void SynthVoice::changeA135(float a135) {
    this->a135 = a135;
}

void SynthVoice::changeA246(float a246) {
    this->a246 = a246;
}

void SynthVoice::changeA789(float a789) {
    this->a789 = a789;
}

void SynthVoice::changeSub(float sub) {
    this->sub = sub;
}

void SynthVoice::changeVar135(float var135) {
    var135Distribution = std::normal_distribution<double>(0.0, var135);
}

void SynthVoice::changeVar246(float var246) {
    var246Distribution = std::normal_distribution<double>(0.0, var246);
}

void SynthVoice::changeVar789(float var789) {
    var789Distribution = std::normal_distribution<double>(0.0, var789);
}

void SynthVoice::changePitch135(float pitch135){
    pitch135Distribution = std::normal_distribution<double>(0.0, pitch135);
}

void SynthVoice::changePitch246(float pitch246) {
    pitch246Distribution = std::normal_distribution<double>(0.0, pitch246);
}

void SynthVoice::changePitch789(float pitch789) {
    pitch789Distribution = std::normal_distribution<double>(0.0, pitch789);
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

void SynthVoice::changeGain(float gain) {
    this->gain = gain;
}

Envelope SynthVoice::getEnvelope() {
    return envelope;
}

void SynthVoice::renderNextBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples)
{
    while(--numSamples >= 0) {
        const float realLevel = ((tailOff > 0) ? (level * tailOff) : level);
        
        double value = 0;
        
        value += (osc[0].getSample() * toneAmp) + (osc[10].getSample() * sub);
        value += (osc[1].getSample() + osc[3].getSample() + osc[5].getSample()) * a135;
        value += (osc[2].getSample() + osc[4].getSample() + osc[6].getSample()) * a246;
        value += (osc[7].getSample() + osc[8].getSample() + osc[9].getSample()) * a789;
        
        double envelopeSample = envelope.nextSample();
        float currentSample = value * realLevel * envelopeSample;
        currentSample = filter.nextSample(currentSample);
        currentSample *= gain;
        
        if(envelopeSample == 0.0)
            clearCurrentNote();
        
        for(int i = outputBuffer.getNumChannels(); --i >= 0;)
            outputBuffer.addSample(i, startSample, currentSample);
        
        ++startSample;
    }

}
