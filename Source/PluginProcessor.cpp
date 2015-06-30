#include "PluginProcessor.h"
#include "PluginEditor.h"

StocSynthAudioProcessor::StocSynthAudioProcessor()
{
    for (int i = 0; i < 4; i++) {
        synth.addVoice(new OscillatorVoice());
    }
    
    synth.addSound (new OscillatorSound());
}

StocSynthAudioProcessor::~StocSynthAudioProcessor()
{
}

void StocSynthAudioProcessor::changeWaveform(Waveform waveform) {
    for(int i = 0; i < 4; i++) {
        OscillatorVoice* voice = static_cast<OscillatorVoice*> (synth.getVoice(i));
        voice->changeWaveform(waveform);
    }
}

const String StocSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int StocSynthAudioProcessor::getNumParameters()
{
    return 0;
}

float StocSynthAudioProcessor::getParameter (int index)
{
    return 0.0f;
}

void StocSynthAudioProcessor::setParameter (int index, float newValue)
{
    switch(index) {
        case WAVE_PARAM:
            switch ((int) newValue) {
                case 1:
                    changeWaveform(Waveform::SINE);
                    break;
                case 2:
                    changeWaveform(Waveform::SQUARE);
                    break;
                case 3:
                    changeWaveform(Waveform::SAW);
                    break;
                case 4:
                    changeWaveform(Waveform::TRIANGLE);
                    break;
                default:
                    break;
            }
            break;
    }
}

const String StocSynthAudioProcessor::getParameterName (int index)
{
    return String();
}

const String StocSynthAudioProcessor::getParameterText (int index)
{
    return String();
}

const String StocSynthAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String StocSynthAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool StocSynthAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool StocSynthAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool StocSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool StocSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool StocSynthAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double StocSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int StocSynthAudioProcessor::getNumPrograms()
{
    return 1;
}

int StocSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void StocSynthAudioProcessor::setCurrentProgram (int index)
{
}

const String StocSynthAudioProcessor::getProgramName (int index)
{
    return String();
}

void StocSynthAudioProcessor::changeProgramName (int index, const String& newName)
{
}

void StocSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate (sampleRate);
}

void StocSynthAudioProcessor::releaseResources()
{
}

void StocSynthAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int numSamples = buffer.getNumSamples();
    
    for (int i = buffer.getNumChannels(); --i >= 0;)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    synth.renderNextBlock (buffer, midiMessages, 0, numSamples);
}

bool StocSynthAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* StocSynthAudioProcessor::createEditor()
{
    return new StocSynthAudioProcessorEditor (*this);
}

void StocSynthAudioProcessor::getStateInformation (MemoryBlock& destData)
{
}

void StocSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new StocSynthAudioProcessor();
}
