#include "PluginProcessor.h"
#include "PluginEditor.h"

StocSynthAudioProcessorEditor::StocSynthAudioProcessorEditor (StocSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    setSize (400, 300);
}

StocSynthAudioProcessorEditor::~StocSynthAudioProcessorEditor()
{
}

void StocSynthAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);

    g.setColour (Colours::black);
    g.setFont (15.0f);
    g.drawFittedText ("4", getLocalBounds(), Justification::centred, 1);
}

void StocSynthAudioProcessorEditor::resized()
{
    
}
