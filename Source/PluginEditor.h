#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class StocSynthAudioProcessorEditor  : public AudioProcessorEditor,
                                       public ComboBoxListener,
                                       public SliderListener,
                                       public Timer
{
public:
    StocSynthAudioProcessorEditor (StocSynthAudioProcessor&);
    ~StocSynthAudioProcessorEditor();

    void timerCallback() override;
    void paint (Graphics&) override;
    void resized() override;
    void comboBoxChanged(ComboBox *comboBox) override;
    void sliderValueChanged(Slider *slider) override;
    void updateGUIValues();

private:
    StocSynthAudioProcessor& processor;
    ComboBox wavebox;
    Slider cutoffSlider;
    Slider resSlider;
    Slider aSlider;
    Slider dSlider;
    Slider sSlider;
    Slider rSlider;
    Slider gainSlider;
    DrawableImage logoImage;
    DrawableImage oscImage;
    DrawableImage filterImage;
    DrawableImage ampImage;
    DrawableImage cutoffImage;
    DrawableImage resImage;
    DrawableImage aImage;
    DrawableImage dImage;
    DrawableImage sImage;
    DrawableImage rImage;
    DrawableImage gainImage;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StocSynthAudioProcessorEditor)
};

#endif  // PLUGINEDITOR_H_INCLUDED
