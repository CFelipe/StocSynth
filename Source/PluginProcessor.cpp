#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SineWave.h"
#include "SquareWave.h"
#include "SawtoothWave.h"


StocSynthAudioProcessor::StocSynthAudioProcessor()
{
    for (int i = 4; --i >= 0;)
        synth.addVoice (new SawtoothWaveVoice());
    
    synth.addSound (new SawtoothWaveSound());
}

StocSynthAudioProcessor::~StocSynthAudioProcessor()
{
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
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
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

//==============================================================================
void StocSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate (sampleRate);
}

void StocSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void StocSynthAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int numSamples = buffer.getNumSamples();
    
    for (int i = buffer.getNumChannels(); --i >= 0;)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    synth.renderNextBlock (buffer, midiMessages, 0, numSamples);
}

//==============================================================================
bool StocSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* StocSynthAudioProcessor::createEditor()
{
    return new StocSynthAudioProcessorEditor (*this);
}

//==============================================================================
void StocSynthAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void StocSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new StocSynthAudioProcessor();
}
