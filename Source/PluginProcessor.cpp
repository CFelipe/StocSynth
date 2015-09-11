#include "PluginProcessor.h"
#include "PluginEditor.h"

#define VOICES 16

StocSynthAudioProcessor::StocSynthAudioProcessor()
{
    for (int i = 0; i < VOICES; i++) {
        synth.addVoice(new SynthVoice());
    }

    synth.addSound (new SynthSound());
    
    changeToneAmp(1.0f);
    changeA135(0.5f);
    changeA246(0.5f);
    changeA789(0.5f);
    changeSub(0.0f);
    changeVar135(0.0f);
    changeVar246(0.0f);
    changeVar789(0.0f);
    
    changeCutoff(0.5f);
    changeRes(0.1f);
    
    changeAmpA(0.01f);
    changeAmpD(0.5f);
    changeAmpS(0.7f);
    changeAmpR(1.0f);
    changeGain(0.7f);
}

StocSynthAudioProcessor::~StocSynthAudioProcessor()
{
}

void StocSynthAudioProcessor::changeToneAmp(float toneAmp) {
    this->toneAmp = toneAmp;
    
    for(int i = 0; i < VOICES; i++) {
        SynthVoice* voice = static_cast<SynthVoice*> (synth.getVoice(i));
        voice->changeToneAmp(toneAmp);
    }
}

void StocSynthAudioProcessor::changeA135(float a135) {
    this->a135 = a135;
    
    for(int i = 0; i < VOICES; i++) {
        SynthVoice* voice = static_cast<SynthVoice*> (synth.getVoice(i));
        voice->changeA135(a135);
    }
}

void StocSynthAudioProcessor::changeA246(float a246) {
    this->a246 = a246;
    
    for(int i = 0; i < VOICES; i++) {
        SynthVoice* voice = static_cast<SynthVoice*> (synth.getVoice(i));
        voice->changeA246(a246);
    }
}

void StocSynthAudioProcessor::changeA789(float a789) {
    this->a789 = a789;
    
    for(int i = 0; i < VOICES; i++) {
        SynthVoice* voice = static_cast<SynthVoice*> (synth.getVoice(i));
        voice->changeA789(a789);
    }
}

void StocSynthAudioProcessor::changeSub(float sub) {
    this->sub = sub;
    
    for(int i = 0; i < VOICES; i++) {
        SynthVoice* voice = static_cast<SynthVoice*> (synth.getVoice(i));
        voice->changeSub(sub);
    }
}

void StocSynthAudioProcessor::changeVar135(float var135) {
    this->var135 = var135;
    
    for(int i = 0; i < VOICES; i++) {
        SynthVoice* voice = static_cast<SynthVoice*> (synth.getVoice(i));
        voice->changeVar135(var135);
    }
}

void StocSynthAudioProcessor::changeVar246(float var246) {
    this->var246 = var246;
    
    for(int i = 0; i < VOICES; i++) {
        SynthVoice* voice = static_cast<SynthVoice*> (synth.getVoice(i));
        voice->changeVar246(var246);
    }
}

void StocSynthAudioProcessor::changeVar789(float var789) {
    this->var789 = var789;
    
    for(int i = 0; i < VOICES; i++) {
        SynthVoice* voice = static_cast<SynthVoice*> (synth.getVoice(i));
        voice->changeVar789(var789);
    }
}

void StocSynthAudioProcessor::changePitch135(float pitch135) {
    this->pitch135 = pitch135;
   
    for(int i = 0; i < VOICES; i++) {
        SynthVoice* voice = static_cast<SynthVoice*> (synth.getVoice(i));
        voice->changePitch135(var135);
    }
}

void StocSynthAudioProcessor::changePitch246(float pitch246) {
    this->pitch246 = pitch246;
    
    for(int i = 0; i < VOICES; i++) {
        SynthVoice* voice = static_cast<SynthVoice*> (synth.getVoice(i));
        voice->changePitch246(var246);
    }
}

void StocSynthAudioProcessor::changePitch789(float pitch789) {
    this->pitch789 = pitch789;
    
    for(int i = 0; i < VOICES; i++) {
        SynthVoice* voice = static_cast<SynthVoice*> (synth.getVoice(i));
        voice->changePitch789(var789);
    }
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
    
    for(int i = 0; i < VOICES; i++) {
        SynthVoice* voice = static_cast<SynthVoice*> (synth.getVoice(i));
        voice->changeGain(gain);
    }
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
        case CUTOFF_PARAM:  return 0.0f;
        default:            return 0.0f;
    }
}

void StocSynthAudioProcessor::setParameter (int index, float newValue)
{
    switch(index) {
        case TONE_AMP_PARAM:
            changeToneAmp(newValue);
            break;
        case A135_PARAM:
            changeA135(newValue);
            break;
        case A246_PARAM:
            changeA246(newValue);
            break;
        case A789_PARAM:
            changeA789(newValue);
            break;
        case SUB_PARAM:
            changeSub(newValue);
            break;
        case VAR135_PARAM:
            changeVar135(newValue);
            break;
        case VAR246_PARAM:
            changeVar246(newValue);
            break;
        case VAR789_PARAM:
            changeVar789(newValue);
            break;
        case PITCH135_PARAM:
            changePitch135(newValue);
            break;
        case PITCH246_PARAM:
            changePitch246(newValue);
            break;
        case PITCH789_PARAM:
            changePitch789(newValue);
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
    XmlElement xml ("STOCSETTINGS");

    xml.setAttribute("toneAmp", toneAmp);
    xml.setAttribute("a135", a135);
    xml.setAttribute("a246", a246);
    xml.setAttribute("a789", a789);
    xml.setAttribute("sub", sub);
    xml.setAttribute("var135", var135);
    xml.setAttribute("var246", var246);
    xml.setAttribute("var789", var789);
    xml.setAttribute("pitch135", pitch135);
    xml.setAttribute("pitch246", pitch246);
    xml.setAttribute("pitch789", pitch789);
    xml.setAttribute("cutoff", cutoff);
    xml.setAttribute("res", res);
    xml.setAttribute("ampA", ampA);
    xml.setAttribute("ampD", ampD);
    xml.setAttribute("ampS", ampS);
    xml.setAttribute("ampR", ampR);
    xml.setAttribute("gain", gain);

    copyXmlToBinary (xml, destData);
}

void StocSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState != nullptr)
    {
        if (xmlState->hasTagName ("STOCSETTINGS"))
        {
            toneAmp = (float) xmlState->getDoubleAttribute("toneAmp", toneAmp);
            a135 = (float) xmlState->getDoubleAttribute("a135", a135);
            a246 = (float) xmlState->getDoubleAttribute("a246", a246);
            a789 = (float) xmlState->getDoubleAttribute("a789", a789);
            sub = (float) xmlState->getDoubleAttribute("sub", sub);
            var135 = (float) xmlState->getDoubleAttribute("var135", var135);
            var246 = (float) xmlState->getDoubleAttribute("var246", var246);
            var789 = (float) xmlState->getDoubleAttribute("var789", var789);
            pitch135 = (float) xmlState->getDoubleAttribute("pitch135", pitch135);
            pitch246 = (float) xmlState->getDoubleAttribute("pitch246", pitch246);
            pitch789 = (float) xmlState->getDoubleAttribute("pitch789", pitch789);
            cutoff = (float) xmlState->getDoubleAttribute("cutoff", cutoff);
            res = (float) xmlState->getDoubleAttribute("res", res);
            ampA = (float) xmlState->getDoubleAttribute("ampA", ampA);
            ampD = (float) xmlState->getDoubleAttribute("ampD", ampD);
            ampS = (float) xmlState->getDoubleAttribute("ampS", ampS);
            ampR = (float) xmlState->getDoubleAttribute("ampR", ampR);
            gain  = (float) xmlState->getDoubleAttribute ("gain", gain);
        }
    }
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new StocSynthAudioProcessor();
}
