#ifndef __StocSynth__SineWave__
#define __StocSynth__SineWave__

#include "../JuceLibraryCode/JuceHeader.h"

class SineWaveSound : public SynthesiserSound
{
public:
    SineWaveSound() {}
    
    bool appliesToNote (int /*midiNoteNumber*/) override  { return true; }
    bool appliesToChannel (int /*midiChannel*/) override  { return true; }
};

class SineWaveVoice  : public SynthesiserVoice
{
public:
    SineWaveVoice();
    
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

private:
    double currentAngle, angleDelta, level, tailOff;
};

#endif /* defined(__StocSynth__SineWave__) */
