#include "PluginProcessor.h"
#include "PluginEditor.h"

#define DIM_W 630
#define DIM_H 290

struct CustomLookAndFeel: public LookAndFeel_V3
{
    void drawRoundThumb (Graphics& g, const float x, const float y,
                         const float diameter, const Colour& colour, float outlineThickness)
    {
        const Rectangle<float> a (x, y, diameter, diameter);
        const float halfThickness = outlineThickness * 0.5f;
        
        Path p;
        p.addEllipse (x + halfThickness, y + halfThickness, diameter - outlineThickness, diameter - outlineThickness);
        
        const DropShadow ds (Colours::black, 1, Point<int> (0, 0));
        ds.drawForPath (g, p);
        
        g.setColour(Colour(182, 195, 168));
        g.fillPath (p);
        
        g.setColour(Colour(37, 37, 37));
        g.strokePath (p, PathStrokeType (outlineThickness));
    }
    
    void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
                               bool isMouseOverButton, bool isButtonDown) override
    {
        Colour baseColour (backgroundColour.withMultipliedSaturation (button.hasKeyboardFocus (true) ? 1.3f : 0.9f)
                           .withMultipliedAlpha (button.isEnabled() ? 0.9f : 0.5f));
        
        if (isButtonDown || isMouseOverButton)
            baseColour = baseColour.contrasting (isButtonDown ? 0.2f : 0.1f);
        
        const bool flatOnLeft   = button.isConnectedOnLeft();
        const bool flatOnRight  = button.isConnectedOnRight();
        const bool flatOnTop    = button.isConnectedOnTop();
        const bool flatOnBottom = button.isConnectedOnBottom();
        
        const float width  = button.getWidth() - 1.0f;
        const float height = button.getHeight() - 1.0f;
        
        if (width > 0 && height > 0)
        {
            const float cornerSize = jmin (15.0f, jmin (width, height) * 0.45f);
            const float lineThickness = cornerSize * 0.1f;
            const float halfThickness = lineThickness * 0.5f;
            
            Path outline;
            outline.addRoundedRectangle (0.5f + halfThickness, 0.5f + halfThickness, width - lineThickness, height - lineThickness,
                                         cornerSize, cornerSize,
                                         ! (flatOnLeft  || flatOnTop),
                                         ! (flatOnRight || flatOnTop),
                                         ! (flatOnLeft  || flatOnBottom),
                                         ! (flatOnRight || flatOnBottom));
            
            const Colour outlineColour (button.findColour (button.getToggleState() ? TextButton::textColourOnId
                                                           : TextButton::textColourOffId));
            
            g.setColour (baseColour);
            g.fillPath (outline);
            
            if (! button.getToggleState())
            {
                g.setColour (outlineColour);
                g.strokePath (outline, PathStrokeType (lineThickness));
            }
        }
    }
    
    void drawTickBox (Graphics& g, Component& component,
                      float x, float y, float w, float h,
                      bool ticked,
                      bool isEnabled,
                      bool isMouseOverButton,
                      bool isButtonDown) override
    {
        const float boxSize = w * 0.7f;
        
        bool isDownOrDragging = component.isEnabled() && (component.isMouseOverOrDragging() || component.isMouseButtonDown());
        const Colour colour (component.findColour (TextButton::buttonColourId).withMultipliedSaturation ((component.hasKeyboardFocus (false) || isDownOrDragging) ? 1.3f : 0.9f)
                             .withMultipliedAlpha (component.isEnabled() ? 1.0f : 0.7f));
        
        drawRoundThumb (g, x, y + (h - boxSize) * 0.5f, boxSize, colour,
                        isEnabled ? ((isButtonDown || isMouseOverButton) ? 1.1f : 0.5f) : 0.3f);
        
        if (ticked)
        {
            const Path tick (LookAndFeel_V2::getTickShape (6.0f));
            g.setColour (isEnabled ? findColour (TextButton::buttonOnColourId) : Colours::grey);
            
            const float scale = 9.0f;
            const AffineTransform trans (AffineTransform::scale (w / scale, h / scale)
                                         .translated (x - 2.5f, y + 1.0f));
            g.fillPath (tick, trans);
        }
    }
    
    void drawLinearSliderThumb (Graphics& g, int x, int y, int width, int height,
                                float sliderPos, float minSliderPos, float maxSliderPos,
                                const Slider::SliderStyle style, Slider& slider) override
    {

        const float sliderRadius = 9;
        
        bool isDownOrDragging = slider.isEnabled() && (slider.isMouseOverOrDragging() || slider.isMouseButtonDown());
        Colour knobColour (slider.findColour (Slider::thumbColourId).withMultipliedSaturation ((slider.hasKeyboardFocus (false) || isDownOrDragging) ? 1.3f : 0.9f)
                           .withMultipliedAlpha (slider.isEnabled() ? 1.0f : 0.7f));
        
        if (style == Slider::LinearHorizontal || style == Slider::LinearVertical)
        {
            float kx, ky;
            
            if (style == Slider::LinearVertical)
            {
                kx = x + width * 0.5f;
                ky = sliderPos;
            }
            else
            {
                kx = sliderPos;
                ky = y + height * 0.5f;
            }
            
            drawRoundThumb (g,
                            kx - sliderRadius,
                            ky - sliderRadius,
                            sliderRadius * 2.0f,
                            knobColour, 2);
        }
        else
        {
            LookAndFeel_V2::drawLinearSliderThumb (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
        }
    }
    
    void drawLinearSlider (Graphics& g, int x, int y, int width, int height,
                           float sliderPos, float minSliderPos, float maxSliderPos,
                           const Slider::SliderStyle style, Slider& slider) override
    {        
        if (style == Slider::LinearBar || style == Slider::LinearBarVertical)
        {
            const float fx = (float) x, fy = (float) y, fw = (float) width, fh = (float) height;
            
            Path p;
            
            if (style == Slider::LinearBarVertical)
                p.addRectangle (fx, sliderPos, fw, 1.0f + fh - sliderPos);
            else
                p.addRectangle (fx, fy, sliderPos - fx, fh);
            
            
            Colour baseColour (slider.findColour (Slider::rotarySliderFillColourId)
                               .withMultipliedSaturation (slider.isEnabled() ? 1.0f : 0.5f)
                               .withMultipliedAlpha (0.8f));
            
            g.setColour (baseColour);
            g.fillPath (p);
            
            const float lineThickness = jmin (15.0f, jmin (width, height) * 0.45f) * 0.1f;
            g.drawRect (slider.getLocalBounds().toFloat(), lineThickness);
        }
        else
        {
            drawLinearSliderBackground (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
            drawLinearSliderThumb (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
        }
    }
    
    void drawLinearSliderBackground (Graphics& g, int x, int y, int width, int height,
                                     float /*sliderPos*/,
                                     float /*minSliderPos*/,
                                     float /*maxSliderPos*/,
                                     const Slider::SliderStyle /*style*/, Slider& slider) override
    {
        Path on, off;
        
        if (slider.isHorizontal())
        {
            // Not happening yet
        }
        else
        {
            DrawableImage sliderOverlayImage;
            Image sliderOverlayIcon = ImageCache::getFromMemory(BinaryData::slider_overlay_png,
                                                                BinaryData::slider_overlay_pngSize);
            sliderOverlayImage.setImage(sliderOverlayIcon);
            sliderOverlayImage.drawAt(g, x, y, 1.0f);
        }
        
        g.setColour(Colour(37, 37, 37));
        g.fillPath(on);
        g.fillPath(off);
    }
    
    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                           float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override
    {
        // Very messy but does the job :)
        const float radius = 9.0f;
        const float centreX = x + 33 * 0.5f;
        const float centreY = y + 33 * 0.5f;
        const float rx = centreX - radius;
        const float ry = centreY - radius;
        const float rw = radius * 2.0f;
        const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        
        {
            DrawableImage knobOverlayImage;
            Image knobOverlayIcon = ImageCache::getFromMemory(BinaryData::knob_overlay_png,
                                                              BinaryData::knob_overlay_pngSize);
            knobOverlayImage.setImage(knobOverlayIcon);
            knobOverlayImage.drawAt(g, x, y, 1.0f);
            
            Path knob;
            g.setColour(Colour(251, 222, 146));
            knob.addEllipse(rx, ry, rw, rw);
            g.fillPath (knob);
            
            Path indicator;
            g.setColour(Colour(38, 38, 38));
            indicator.addRectangle(centreX - 1, ry + 1, 2, 7);
            g.saveState();
            g.addTransform(AffineTransform::identity.translated(-centreX, -centreY).rotated(angle).translated(centreX, centreY));
            g.fillPath(indicator);
            g.restoreState();
        }
        
        {
            Path outline;
            outline.addEllipse(rx, ry, rw, rw);
            g.strokePath(outline, PathStrokeType (2));
        }
    }
};

void StocSynthAudioProcessorEditor::addKnob(Slider *knob, int x, int y) {
    knob->setRange(0.0, 1.0, 0.001);
    knob->setSliderStyle(Slider::RotaryVerticalDrag);
    knob->setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    knob->setBounds(x, y, 32, 32);
    knob->setDoubleClickReturnValue (true, 1.0);
    knob->setMouseDragSensitivity(127);
    knob->addListener(this);
    addAndMakeVisible(knob);
}

void StocSynthAudioProcessorEditor::addSlider(Slider *slider, int x, int y, int rangeMin, int rangeMax, int doubleClickValue) {
    slider->setRange (0.0, 0.99, 0.001);
    slider->setSliderStyle (Slider::LinearVertical);
    slider->setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    slider->setBounds (x, y, 33, 145);
    slider->setDoubleClickReturnValue (true, 0.90);
    slider->addListener(this);
    addAndMakeVisible(slider);
}

StocSynthAudioProcessorEditor::StocSynthAudioProcessorEditor (StocSynthAudioProcessor& p)
    : AudioProcessorEditor(&p),
      processor(p),
      cutoffSlider(),
      resSlider(),
      aSlider(),
      dSlider(),
      sSlider(),
      rSlider(),
      toneKnob(),
      a135Knob(),
      a246Knob(),
      a789Knob(),
      subKnob(),
      var135Knob(),
      var246Knob(),
      var789Knob(),
      pitch135Knob(),
      pitch246Knob(),
      pitch789Knob()
{
    setSize (DIM_W, DIM_H);
    
    LookAndFeel *laf = new CustomLookAndFeel();
    setLookAndFeel(laf);
    
    const float sliderY = 101;
    
    addSlider(&cutoffSlider, 210, sliderY, 0.0f, 0.99f, 0.90f);
    addSlider(&resSlider,    268, sliderY, 0.0f, 1.0f, 0.1f);
    addSlider(&aSlider,      340, sliderY, 0.0f, 1.0f, 0.5f);
    addSlider(&dSlider,      397, sliderY, 0.0f, 1.0f, 0.5f);
    addSlider(&sSlider,      454, sliderY, 0.0f, 1.0f, 0.5f);
    addSlider(&rSlider,      511, sliderY, 0.0f, 1.0f, 0.5f);
    addSlider(&gainSlider,   568, sliderY, 0.0f, 1.0f, 0.7f);
    
    const float colPadY = 58;
    const float col1Y = 100;
    const float col2Y = col1Y + colPadY;
    const float col3Y = col2Y + colPadY;
    
    addKnob(&toneKnob, 22,  col1Y);
    addKnob(&a135Knob, 63,  col1Y);
    addKnob(&a246Knob, 104, col1Y);
    addKnob(&a789Knob, 145, col1Y);
    
    addKnob(&subKnob,    22,  col2Y);
    addKnob(&var135Knob, 63,  col2Y);
    addKnob(&var246Knob, 104, col2Y);
    addKnob(&var789Knob, 145, col2Y);
    
    addKnob(&pitch135Knob, 63,  col3Y);
    addKnob(&pitch246Knob, 104, col3Y);
    addKnob(&pitch789Knob, 145, col3Y);

    Image logoIcon = ImageCache::getFromMemory(BinaryData::logo_png,
                                               BinaryData::logo_pngSize);
    
    Image panelOverlaysIcon = ImageCache::getFromMemory(BinaryData::panel_overlays_png,
                                                        BinaryData::panel_overlays_pngSize);
    
    Image oscIcon = ImageCache::getFromMemory(BinaryData::osc_title_png,
                                              BinaryData::osc_title_pngSize);
    
    Image filterIcon = ImageCache::getFromMemory(BinaryData::filter_title_png,
                                                 BinaryData::filter_title_pngSize);
    
    Image ampIcon = ImageCache::getFromMemory(BinaryData::amp_title_png,
                                              BinaryData::amp_title_pngSize);
    
    Image cutoffIcon = ImageCache::getFromMemory(BinaryData::cutoff_png,
                                                 BinaryData::cutoff_pngSize);
    
    Image resIcon = ImageCache::getFromMemory(BinaryData::res_png,
                                              BinaryData::res_pngSize);
    
    Image aIcon = ImageCache::getFromMemory(BinaryData::a_png,
                                            BinaryData::a_pngSize);

    Image dIcon = ImageCache::getFromMemory(BinaryData::d_png,
                                            BinaryData::d_pngSize);

    Image sIcon = ImageCache::getFromMemory(BinaryData::s_png,
                                            BinaryData::s_pngSize);

    Image rIcon = ImageCache::getFromMemory(BinaryData::r_png,
                                            BinaryData::r_pngSize);
    
    Image gainIcon = ImageCache::getFromMemory(BinaryData::gain_png,
                                               BinaryData::gain_pngSize);
    
    Image knobOverlayIcon = ImageCache::getFromMemory(BinaryData::knob_overlay_png,
                                                      BinaryData::knob_overlay_pngSize);
    
    Image sliderOverlayIcon = ImageCache::getFromMemory(BinaryData::slider_overlay_png,
                                                        BinaryData::slider_overlay_pngSize);

    logoImage.setImage(logoIcon);
    panelOverlaysImage.setImage(panelOverlaysIcon);
    oscImage.setImage(oscIcon);
    filterImage.setImage(filterIcon);
    ampImage.setImage(ampIcon);
    cutoffImage.setImage(cutoffIcon);
    resImage.setImage(resIcon);
    aImage.setImage(aIcon);
    dImage.setImage(dIcon);
    sImage.setImage(sIcon);
    rImage.setImage(rIcon);
    gainImage.setImage(gainIcon);
    
    updateGUIValues();
    startTimer(50);
    
}

StocSynthAudioProcessorEditor::~StocSynthAudioProcessorEditor()
{
}

void StocSynthAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(Colour(55, 55, 55));
    g.setColour(Colour(230, 230, 230));
    
    Path outline;
    outline.addRectangle(5, 5, DIM_W - 10, DIM_H - 10);
    g.strokePath(outline, PathStrokeType(2));
    
    /*
    outline.addLineSegment(Line<float>(205, 60, 306, 60), 0);
    g.strokePath(outline, PathStrokeType(2));
    
    outline.addLineSegment(Line<float>(328, 60, 565, 60), 0);
    g.strokePath(outline, PathStrokeType(2));
     */
    
    logoImage.drawAt(g, 25, 25, 1.0f);
    
    panelOverlaysImage.drawAt(g, 21, 60, 1.0f);
    
    /*
    oscImage.drawAt(g, 31, 69, 1.0f);
    filterImage.drawAt(g, 218, 69, 1.0f);
    ampImage.drawAt(g, 338, 69, 1.0f);
     */
    
    const float labelY = 254;
    cutoffImage.drawAt(g, 206, labelY, 1.0f);
    resImage.drawAt(   g, 273, labelY, 1.0f);
    aImage.drawAt(     g, 353, labelY, 1.0f);
    dImage.drawAt(     g, 411, labelY, 1.0f);
    sImage.drawAt(     g, 466, labelY, 1.0f);
    rImage.drawAt(     g, 524, labelY, 1.0f);
    gainImage.drawAt(  g, 572, labelY, 1.0f);
    
    g.setFont (16.0f);
}

void StocSynthAudioProcessorEditor::resized()
{
    // Won't happen
}

void StocSynthAudioProcessorEditor::comboBoxChanged(ComboBox *comboBox) {
    // No comboboxes as of now
}

// Updates the GUI periodically from possible host automation
void StocSynthAudioProcessorEditor::timerCallback()
{
    updateGUIValues();
}

void StocSynthAudioProcessorEditor::updateGUIValues()
{
    cutoffSlider.setValue (processor.cutoff, dontSendNotification);
    resSlider.setValue (processor.res, dontSendNotification);
    aSlider.setValue (processor.ampA, dontSendNotification);
    dSlider.setValue (processor.ampD, dontSendNotification);
    sSlider.setValue (processor.ampS, dontSendNotification);
    rSlider.setValue (processor.ampR, dontSendNotification);
    gainSlider.setValue (processor.gain, dontSendNotification);
}

void StocSynthAudioProcessorEditor::sliderValueChanged(Slider *slider) {
    if(slider == &cutoffSlider) {
        processor.setParameterNotifyingHost (StocSynthAudioProcessor::CUTOFF_PARAM,
                                             slider->getValue());
    } else if(slider == &resSlider) {
        processor.setParameterNotifyingHost (StocSynthAudioProcessor::RES_PARAM,
                                             slider->getValue());
    } else if(slider == &aSlider) {
        processor.setParameterNotifyingHost (StocSynthAudioProcessor::AMP_A_PARAM,
                                             slider->getValue());
    } else if(slider == &dSlider) {
        processor.setParameterNotifyingHost (StocSynthAudioProcessor::AMP_D_PARAM,
                                             slider->getValue());
    } else if(slider == &sSlider) {
        processor.setParameterNotifyingHost (StocSynthAudioProcessor::AMP_S_PARAM,
                                             slider->getValue());
    } else if(slider == &rSlider) {
        processor.setParameterNotifyingHost (StocSynthAudioProcessor::AMP_R_PARAM,
                                             slider->getValue());
    } else if(slider == &gainSlider) {
        processor.setParameterNotifyingHost (StocSynthAudioProcessor::GAIN_PARAM,
                                             slider->getValue());
    }
}