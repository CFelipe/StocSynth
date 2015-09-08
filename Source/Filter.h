#ifndef __StocSynth__Filter__
#define __StocSynth__Filter__

#include <stdio.h>
// Mostly taken from http://www.musicdsp.org/showArchiveComment.php?ArchiveID=24

class Filter
{
public:
    float nextSample(float input);
    void setSampleRate(float newSampleRate);
    void setCutoff(float cutoff);
    void setResonance(float resonance);
    
    Filter() :
    sampleRate(44100.0),
    cutoff(0.5),
    res(0.1),
    buf0(0.0),
    buf1(0.0) {
        calculateFeedbackAmount();
    };

private:
    float sampleRate;
    float cutoff;
    float res;
    float buf0;
    float buf1;
    float feedbackAmount;
    inline void calculateFeedbackAmount() { feedbackAmount = res + res/(1.0 - cutoff); }
};


#endif