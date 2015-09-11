#ifndef __StocSynth__SynthVoice__
#define __StocSynth__SynthVoice__

#include "../JuceLibraryCode/JuceHeader.h"
#include "Envelope.h"
#include "Filter.h"
#include "Oscillator.h"
#include <cmath>
#include <random>

class SynthSound : public SynthesiserSound
{
public:
    SynthSound() {}
    
    bool appliesToNote (int /*midiNoteNumber*/) override  { return true; }
    bool appliesToChannel (int /*midiChannel*/) override  { return true; }
};

class SynthVoice  : public SynthesiserVoice
{
public:
    SynthVoice();
    
    bool canPlaySound(SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity,
                    SynthesiserSound* /*sound*/,
                    int /*currentPitchWheelPosition*/) override;
    void stopNote (float /*velocity*/, bool allowTailOff) override;
    void renderNextBlock (AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override;
    
    void pitchWheelMoved (int /*newValue*/) override
    {
    }
    
    void controllerMoved (int /*controllerNumber*/, int /*newValue*/) override
    {
    }
    
    void changeToneAmp(float toneAmp);
    void changeA135(float a135);
    void changeA246(float a246);
    void changeA789(float a789);
    void changeSub(float sub);
    void changeVar135(float var135);
    void changeVar246(float var246);
    void changeVar789(float var789);
    void changePitch135(float pitch135);
    void changePitch246(float pitch246);
    void changePitch789(float pitch789);
    
    void changeCutoff(float cutoff);
    void changeRes(float res);
    void changeAmpA(float a);
    void changeAmpD(float d);
    void changeAmpS(float s);
    void changeAmpR(float r);
    void changeGain(float gain);
    
    Envelope getEnvelope();
    
private:
    double level, tailOff, prevOut;
    float toneAmp;
    float a135;
    float a246;
    float a789;
    float sub;
    float var135;
    float var246;
    float var789;
    float pitch135;
    float pitch246;
    float pitch789;
    float gain;
    
    Envelope envelope;
    Filter filter;
    Oscillator osc[11];
    double randomAmps[11];
    
    std::default_random_engine generator;
    std::normal_distribution<double> var135Distribution;
    std::normal_distribution<double> var246Distribution;
    std::normal_distribution<double> var789Distribution;
    std::normal_distribution<double> pitch135Distribution;
    std::normal_distribution<double> pitch246Distribution;
    std::normal_distribution<double> pitch789Distribution;
};

#endif /* defined(__StocSynth__SynthVoice__) */
