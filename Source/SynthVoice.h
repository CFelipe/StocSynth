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
    
    void changeCutoff(float cutoff);
    void changeRes(float res);
    void changeAmpA(float a);
    void changeAmpD(float d);
    void changeAmpS(float s);
    void changeAmpR(float r);
    Envelope getEnvelope();
    
private:
    double level, tailOff, prevOut;
    Envelope envelope;
    Filter filter;
    Oscillator osc[10];
    double randomAmps[10];
    
    std::default_random_engine generator;
    std::normal_distribution<double> distribution;
};

#endif /* defined(__StocSynth__SynthVoice__) */
