#include "PluginProcessor.h"
#include "PluginEditor.h"

#define VOICES 8

StocSynthAudioProcessor::StocSynthAudioProcessor()
{
    gain = 0.7;
    ampA = 0.01;
    ampD = 0.5;
    ampS = 0.7;
    ampR = 3.0;

    for (int i = 0; i < VOICES; i++) {
        synth.addVoice(new SynthVoice());
    }
    
    synth.addSound (new SynthSound());
}

StocSynthAudioProcessor::~StocSynthAudioProcessor()
{
}

// Code from before this becoming an additive synthesiser
void StocSynthAudioProcessor::changeWaveform(Waveform waveform) {
    /*
    for(int i = 0; i < VOICES; i++) {
        SynthVoice* voice = static_cast<SynthVoice*> (synth.getVoice(i));
        voice->changeWaveform(waveform);
    }
     */
}


void StocSynthAudioProcessor::changeCutoff(float cutoff) {
    this->cutoff = cutoff;
    
    for(int i = 0; i < VOICES; i++) {
        SynthVoice* voice = static_cast<SynthVoice*> (synth.getVoice(i));
        voice->changeCutoff(cutoff);
    }
}

void StocSynthAudioProcessor::changeRes(float res) {
    this->res = res;
    
    for(int i = 0; i < VOICES; i++) {
        SynthVoice* voice = static_cast<SynthVoice*> (synth.getVoice(i));
        voice->changeRes(res);
    }
}

void StocSynthAudioProcessor::changeAmpA(float a) {
    this->ampA = a;
    
    for(int i = 0; i < VOICES; i++) {
        SynthVoice* voice = static_cast<SynthVoice*> (synth.getVoice(i));
        voice->changeAmpA(a);
    }
}

void StocSynthAudioProcessor::changeAmpD(float d) {
    this->ampD = d;
    
    for(int i = 0; i < VOICES; i++) {
        SynthVoice* voice = static_cast<SynthVoice*> (synth.getVoice(i));
        voice->changeAmpD(d);
    }
}

void StocSynthAudioProcessor::changeAmpS(float s) {
    this->ampS = s;
    
    for(int i = 0; i < VOICES; i++) {
        SynthVoice* voice = static_cast<SynthVoice*> (synth.getVoice(i));
        voice->changeAmpS(s);
    }
}

void StocSynthAudioProcessor::changeAmpR(float r) {
    this-> ampR = r;
    
    for(int i = 0; i < VOICES; i++) {
        SynthVoice* voice = static_cast<SynthVoice*> (synth.getVoice(i));
        voice->changeAmpR(r);
    }
}

void StocSynthAudioProcessor::changeGain(float gain) {
    this->gain = gain;
}

const String StocSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int StocSynthAudioProcessor::getNumParameters()
{
    return totalNumParams;
}

float StocSynthAudioProcessor::getParameter (int index)
{
    switch (index)
    {
        case WAVE_PARAM:    return 0.0f;
        case CUTOFF_PARAM:  return 0.0f;
        default:            return 0.0f;
    }
}

void StocSynthAudioProcessor::setParameter (int index, float newValue)
{
    switch(index) {
        case WAVE_PARAM:
            changeWaveform(static_cast<Waveform>((int) newValue));
            break;
        case CUTOFF_PARAM:
            changeCutoff(newValue);
            break;
        case RES_PARAM:
            changeRes(newValue);
            break;
        case AMP_A_PARAM:
            changeAmpA(newValue);
            break;
        case AMP_D_PARAM:
            changeAmpD(newValue);
            break;
        case AMP_S_PARAM:
            changeAmpS(newValue);
            break;
        case AMP_R_PARAM:
            changeAmpR(newValue);
            break;
        case GAIN_PARAM:
            changeGain(newValue);
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
    // Create an outer XML element..
    XmlElement xml ("MYPLUGINSETTINGS");
    
    xml.setAttribute("cutoff", cutoff);
    xml.setAttribute("res", res);
    xml.setAttribute("ampA", ampA);
    xml.setAttribute("ampD", ampD);
    xml.setAttribute("ampS", ampS);
    xml.setAttribute("ampR", ampR);
    xml.setAttribute ("gain", gain);
    
    copyXmlToBinary (xml, destData);
}

void StocSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    
    if (xmlState != nullptr)
    {
        if (xmlState->hasTagName ("MYPLUGINSETTINGS"))
        {
            cutoff = (float) xmlState->getDoubleAttribute("cutoff", cutoff);
            gain  = (float) xmlState->getDoubleAttribute ("gain", gain);
        }
    }
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new StocSynthAudioProcessor();
}
