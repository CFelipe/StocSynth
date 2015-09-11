#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthVoice.h"
#include "Envelope.h"

class StocSynthAudioProcessor  : public AudioProcessor
{
public:
    StocSynthAudioProcessor();
    ~StocSynthAudioProcessor();

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const String getName() const override;

    int getNumParameters() override;
    float getParameter (int index) override;
    void setParameter (int index, float newValue) override;

    const String getParameterName (int index) override;
    const String getParameterText (int index) override;

    const String getInputChannelName (int channelIndex) const override;
    const String getOutputChannelName (int channelIndex) const override;
    bool isInputChannelStereoPair (int index) const override;
    bool isOutputChannelStereoPair (int index) const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool silenceInProducesSilenceOut() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void changeToneAmp(float toneAmp);
    void changeA135(float a135);
    void changeA246(float a246);
    void changeA789(float a789);
    void changeSub(float sub);
    void changeVar135(float var135);
    void changeVar246(float var246);
    void changeVar789(float var789);
    void changePitch135(float pitch135);
    void changePitch246(float pitch246);
    void changePitch789(float pitch789);
    
    void changeCutoff(float cutoff);
    void changeRes(float res);
                   
    void changeAmpA(float a);
    void changeAmpD(float d);
    void changeAmpS(float s);
    void changeAmpR(float r);
    void changeGain(float g);

    Synthesiser synth;

    float toneAmp;
    float a135;
    float a246;
    float a789;
    float sub;
    float var135;
    float var246;
    float var789;
    float pitch135;
    float pitch246;
    float pitch789;

    float cutoff;
    float res;

    float ampA;
    float ampD;
    float ampS;
    float ampR;
    float gain;

    enum Parameters
    {
        WAVE_PARAM = 0,
        TONE_AMP_PARAM,
        A135_PARAM,
        A246_PARAM,
        A789_PARAM,
        SUB_PARAM,
        VAR135_PARAM,
        VAR246_PARAM,
        VAR789_PARAM,
        PITCH135_PARAM,
        PITCH246_PARAM,
        PITCH789_PARAM,
        CUTOFF_PARAM,
        RES_PARAM,
        AMP_A_PARAM,
        AMP_D_PARAM,
        AMP_S_PARAM,
        AMP_R_PARAM,
        GAIN_PARAM,
        totalNumParams
    };

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StocSynthAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
