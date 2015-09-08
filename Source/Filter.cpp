#include "Filter.h"
#include <cmath>

float Filter::nextSample(float input) {
    buf0 += cutoff * (input - buf0 + feedbackAmount * (buf0 - buf1));
    buf1 += cutoff * (buf0 - buf1);
    
    return buf1;
}

void Filter::setSampleRate(float newSampleRate) {
    sampleRate = newSampleRate;
    calculateFeedbackAmount();
}

void Filter::setCutoff(float cutoff) {
    this->cutoff = cutoff;
    calculateFeedbackAmount();
}

void Filter::setResonance(float resonance) {
    this->res = resonance;
    calculateFeedbackAmount();
}