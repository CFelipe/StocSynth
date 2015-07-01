#ifndef __StocSynth__Oscillator__
#define __StocSynth__Oscillator__

#include "../JuceLibraryCode/JuceHeader.h"
#include "Envelope.h"
#include <random>

enum Waveform {SINE = 1, SQUARE, SAW, TRIANGLE};

class OscillatorSound : public SynthesiserSound
{
public:
    OscillatorSound() {}
    
    bool appliesToNote (int /*midiNoteNumber*/) override  { return true; }
    bool appliesToChannel (int /*midiChannel*/) override  { return true; }
};

class OscillatorVoice  : public SynthesiserVoice
{
public:
    OscillatorVoice();
    OscillatorVoice(Waveform waveform);
    
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
    
    double polyBlep(double t);
    double naiveWaveform(Waveform waveform);
    void changeWaveform(Waveform waveform);
    
private:
    double phase, phaseDelta, level, tailOff, prevOut;
    Waveform waveform;
    Envelope envelope;
    
    std::default_random_engine generator;
    std::normal_distribution<double> distribution;
};

#endif /* defined(__StocSynth__Oscillator__) */
