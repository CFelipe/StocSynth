#include "SawtoothWave.h"

SawtoothWaveVoice::SawtoothWaveVoice() : angleDelta (0.0),
tailOff (0.0)
{
}

bool SawtoothWaveVoice::canPlaySound (SynthesiserSound* sound)
{
    return dynamic_cast<SawtoothWaveSound*> (sound) != nullptr;
}

void SawtoothWaveVoice::startNote (int midiNoteNumber, float velocity,
                                 SynthesiserSound* /*sound*/,
                                 int /*currentPitchWheelPosition*/)
{
    currentAngle = 0.0;
    level = velocity * 0.15;
    tailOff = 0.0;
    
    double cyclesPerSecond = MidiMessage::getMidiNoteInHertz (midiNoteNumber);
    double cyclesPerSample = cyclesPerSecond / getSampleRate();
    
    angleDelta = cyclesPerSample * 2.0 * double_Pi;
}

void SawtoothWaveVoice::stopNote (float /*velocity*/, bool allowTailOff)
{
    if (allowTailOff)
    {
        if (tailOff == 0.0)
            tailOff = 1.0;
    }
    else
    {
        clearCurrentNote();
        angleDelta = 0.0;
    }
}

void SawtoothWaveVoice::renderNextBlock (AudioSampleBuffer& outputBuffer, int startSample, int numSamples)
{
    if (angleDelta != 0.0)
    {
        if (tailOff > 0)
        {
            while (--numSamples >= 0)
            {
                const float currentSample = (level * tailOff) - ((currentAngle * level * tailOff) / double_Pi);

                for (int i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample (i, startSample, currentSample);
                
                currentAngle += angleDelta;
                ++startSample;
                
                if (currentAngle > 2 * double_Pi)
                    currentAngle = currentAngle - (2 * double_Pi);
                
                tailOff *= 0.99;
                
                if (tailOff <= 0.005)
                {
                    clearCurrentNote();
                    
                    angleDelta = 0.0;
                    break;
                }
            }
        }
        else
        {
            while (--numSamples >= 0)
            {
                const float currentSample = level - ((currentAngle * level) / double_Pi);
                
                for (int i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample (i, startSample, currentSample);
                
                currentAngle += angleDelta;
                ++startSample;
                
                if (currentAngle > 2 * double_Pi)
                    currentAngle = currentAngle - (2 * double_Pi);
            }
        }
    }
}