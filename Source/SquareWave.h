#ifndef __StocSynth__SquareWave__
#define __StocSynth__SquareWave__

#include "../JuceLibraryCode/JuceHeader.h"

class SquareWaveSound : public SynthesiserSound
{
public:
    SquareWaveSound() {}
    
    bool appliesToNote (int /*midiNoteNumber*/) override  { return true; }
    bool appliesToChannel (int /*midiChannel*/) override  { return true; }
};

class SquareWaveVoice  : public SynthesiserVoice
{
public:
    SquareWaveVoice();
    
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

#endif /* defined(__StocSynth__SquareWave__) */
