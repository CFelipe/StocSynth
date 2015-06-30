#include "PluginProcessor.h"
#include "PluginEditor.h"

StocSynthAudioProcessorEditor::StocSynthAudioProcessorEditor (StocSynthAudioProcessor& p)
    : AudioProcessorEditor (&p),
      processor (p),
      wavebox("Wave"),
      wave("Default")
{
    setSize (400, 300);
    
    wavebox.addItem("Sine", 1);
    wavebox.addItem("Square", 2);
    wavebox.addItem("Saw", 3);
    wavebox.addItem("Triangle", 4);
    wavebox.setBounds (10, 85, 200, 24);
    wavebox.setSelectedId (1);
    wavebox.addListener(this);
    addAndMakeVisible(wavebox);
}

StocSynthAudioProcessorEditor::~StocSynthAudioProcessorEditor()
{
}

void StocSynthAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);

    g.setColour (Colours::black);
    g.setFont (15.0f);
    g.drawFittedText (wave, getLocalBounds(), Justification::centred, 1);
}

void StocSynthAudioProcessorEditor::resized()
{
    
}

void StocSynthAudioProcessorEditor::comboBoxChanged(ComboBox *comboBox) {
    if(comboBox == &wavebox) {
        processor.setParameterNotifyingHost (StocSynthAudioProcessor::WAVE_PARAM,
                                             comboBox->getSelectedId());
        
        wave = std::to_string(comboBox->getSelectedId());
        
        repaint();
    }
}