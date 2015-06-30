#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class StocSynthAudioProcessorEditor  : public AudioProcessorEditor,
                                       public ComboBoxListener
{
public:
    StocSynthAudioProcessorEditor (StocSynthAudioProcessor&);
    ~StocSynthAudioProcessorEditor();

    void paint (Graphics&) override;
    void resized() override;
    void comboBoxChanged(ComboBox *comboBox) override;

private:
    StocSynthAudioProcessor& processor;
    ComboBox wavebox;
    String wave;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StocSynthAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
