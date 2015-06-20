#ifndef __StocSynth__SawtoothWave__
#define __StocSynth__SawtoothWave__

#include "../JuceLibraryCode/JuceHeader.h"

class SawtoothWaveSound : public SynthesiserSound
{
public:
    SawtoothWaveSound() {}
    
    bool appliesToNote (int /*midiNoteNumber*/) override  { return true; }
    bool appliesToChannel (int /*midiChannel*/) override  { return true; }
};

class SawtoothWaveVoice  : public SynthesiserVoice
{
public:
    SawtoothWaveVoice();
    
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

#endif /* defined(__StocSynth__SawtoothWave__) */
