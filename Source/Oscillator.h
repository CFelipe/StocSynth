#ifndef __StocSynth__Oscillator__
#define __StocSynth__Oscillator__

#include "../JuceLibraryCode/JuceHeader.h"
#include <random>

enum Waveform {SINE = 1, SQUARE, SAW, TRIANGLE};

class Oscillator
{
public:
    Oscillator();
    Oscillator(Waveform waveform);
    
    float getSample();
    
    double polyBlep(double t);
    double naiveWaveform(Waveform waveform);
    void changeWaveform(Waveform waveform);
    void setFreq(double freq, double sampleRate);
    
private:
    double phase, phaseDelta, prevOut, level, tailOff, randomPitch, sampleRate;
    Waveform waveform;
};

#endif /* defined(__StocSynth__Oscillator__) */