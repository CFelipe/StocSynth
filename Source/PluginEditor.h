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
    void addKnob(Slider *knob, int x, int y);
    void addSlider(Slider *slider, int x, int y, int rangeMin, int rangeMax, int doubleClickValue);
    void updateGUIValues();

private:
    StocSynthAudioProcessor& processor;
    // Sliders
    Slider cutoffSlider;
    Slider resSlider;
    Slider aSlider;
    Slider dSlider;
    Slider sSlider;
    Slider rSlider;
    Slider gainSlider;
    // Knobs
    Slider toneKnob;
    Slider a135Knob;
    Slider a246Knob;
    Slider a789Knob;
    Slider subKnob;
    Slider var135Knob;
    Slider var246Knob;
    Slider var789Knob;
    Slider pitch135Knob;
    Slider pitch246Knob;
    Slider pitch789Knob;
    // Images
    DrawableImage logoImage;
    DrawableImage panelOverlaysImage;
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
