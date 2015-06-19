#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class StocSynthAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    StocSynthAudioProcessorEditor (StocSynthAudioProcessor&);
    ~StocSynthAudioProcessorEditor();

    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    StocSynthAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StocSynthAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
