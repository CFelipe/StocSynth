#include "PluginProcessor.h"
#include "PluginEditor.h"

#define DIM_W 588
#define DIM_H 277

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
        //const float sliderRadius = (float) (getSliderThumbRadius (slider) - 2);
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
        g.fillAll (slider.findColour (Slider::backgroundColourId));
        
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
        //const float sliderRadius = getSliderThumbRadius (slider) - 5.0f;
        const float sliderRadius = 5;
        Path on, off;
        
        if (slider.isHorizontal())
        {
            const float iy = x + width * 0.5f - sliderRadius * 0.5f;
            Rectangle<float> r (x - sliderRadius * 0.5f, iy, width + sliderRadius, sliderRadius);
            const float onW = r.getWidth() * ((float) slider.valueToProportionOfLength (slider.getValue()));
            
            on.addRectangle (r.removeFromLeft (onW));
            off.addRectangle (r);
        }
        else
        {
            const float ix = x + width * 0.5f - sliderRadius * 0.5f;
            Rectangle<float> r (ix, y - sliderRadius * 0.5f, sliderRadius, height + sliderRadius);
            const float onH = r.getHeight() * ((float) slider.valueToProportionOfLength (slider.getValue()));
            
            on.addRectangle (r.removeFromBottom (onH));
            off.addRectangle (r);
        }
        
        g.setColour(Colour(37, 37, 37));
        g.fillPath (on);
        g.fillPath (off);
    }
    
    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                           float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override
    {
        const float radius = jmin (width / 2, height / 2) - 2.0f;
        const float centreX = x + width * 0.5f;
        const float centreY = y + height * 0.5f;
        const float rx = centreX - radius;
        const float ry = centreY - radius;
        const float rw = radius * 2.0f;
        const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();
        
        if (slider.isEnabled())
            g.setColour (slider.findColour (Slider::rotarySliderFillColourId).withAlpha (isMouseOver ? 1.0f : 0.7f));
        else
            g.setColour (Colour (0x80808080));
        
        {
            Path filledArc;
            filledArc.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, angle, 0.0);
            g.fillPath (filledArc);
        }
        
        {
            const float lineThickness = jmin (15.0f, jmin (width, height) * 0.45f) * 0.1f;
            Path outlineArc;
            outlineArc.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, 0.0);
            g.strokePath (outlineArc, PathStrokeType (lineThickness));
        }
    }
};

StocSynthAudioProcessorEditor::StocSynthAudioProcessorEditor (StocSynthAudioProcessor& p)
    : AudioProcessorEditor(&p),
      processor(p),
      wavebox("Wave"),
      cutoffSlider(),
      resSlider(),
      aSlider(),
      dSlider(),
      sSlider(),
      rSlider()
{
    setSize (DIM_W, DIM_H);
    
    LookAndFeel *laf = new CustomLookAndFeel();
    setLookAndFeel(laf);
    
    wavebox.addItem("SIN", 1);
    wavebox.addItem("SQR", 2);
    wavebox.addItem("SAW", 3);
    wavebox.addItem("TRI", 4);
    wavebox.setBounds (108, 123, 54, 21);
    wavebox.setSelectedId (1);
    wavebox.addListener(this);
    addAndMakeVisible(wavebox);
    
    cutoffSlider.setRange (0.0, 0.99, 0.001);
    cutoffSlider.setSliderStyle (Slider::LinearVertical);
    cutoffSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    cutoffSlider.setBounds (212, 102, 30, 100);
    cutoffSlider.setDoubleClickReturnValue (true, 0.90);
    cutoffSlider.addListener(this);
    addAndMakeVisible(cutoffSlider);
    
    resSlider.setRange (0.0, 1.0, 0.001);
    resSlider.setSliderStyle (Slider::LinearVertical);
    resSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    resSlider.setBounds (266, 102, 30, 100);
    resSlider.setDoubleClickReturnValue (true, 0.1);
    resSlider.addListener(this);
    addAndMakeVisible(resSlider);
    
    aSlider.setRange (0.0, 1.0, 0.001);
    aSlider.setSliderStyle (Slider::LinearVertical);
    aSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    aSlider.setBounds (337, 102, 30, 100);
    aSlider.setDoubleClickReturnValue (true, 0.5);
    aSlider.addListener(this);
    addAndMakeVisible(aSlider);
    
    dSlider.setRange (0.0, 1.0, 0.001);
    dSlider.setSliderStyle (Slider::LinearVertical);
    dSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    dSlider.setBounds (383, 102, 30, 100);
    dSlider.setDoubleClickReturnValue (true, 0.5);
    dSlider.addListener(this);
    addAndMakeVisible(dSlider);
    
    sSlider.setRange (0.0, 1.0, 0.001);
    sSlider.setSliderStyle (Slider::LinearVertical);
    sSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    sSlider.setBounds (430, 102, 30, 100);
    sSlider.setDoubleClickReturnValue (true, 0.5);
    sSlider.addListener(this);
    addAndMakeVisible(sSlider);
    
    rSlider.setRange (0.0, 1.0, 0.001);
    rSlider.setSliderStyle (Slider::LinearVertical);
    rSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    rSlider.setBounds (476, 102, 30, 100);
    rSlider.setDoubleClickReturnValue (true, 0.5);
    rSlider.addListener(this);
    addAndMakeVisible(rSlider);
    
    gainSlider.setRange (0.0, 1.0, 0.001);
    gainSlider.setSliderStyle (Slider::LinearVertical);
    gainSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    gainSlider.setBounds (520, 102, 30, 100);
    gainSlider.setDoubleClickReturnValue (true, 0.7);
    gainSlider.addListener(this);
    addAndMakeVisible(gainSlider);
    
    Image logoIcon = ImageCache::getFromMemory(BinaryData::logo_png,
                                               BinaryData::logo_pngSize);
    
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

    logoImage.setImage(logoIcon);
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
    
    outline.addLineSegment(Line<float>(21, 60, 178, 60), 0);
    g.strokePath(outline, PathStrokeType(2));

    outline.addLineSegment(Line<float>(205, 60, 306, 60), 0);
    g.strokePath(outline, PathStrokeType(2));
    
    outline.addLineSegment(Line<float>(328, 60, 565, 60), 0);
    g.strokePath(outline, PathStrokeType(2));
    
    logoImage.drawAt(g, 15, 15, 1.0f);
    oscImage.drawAt(g, 31, 69, 1.0f);
    filterImage.drawAt(g, 218, 69, 1.0f);
    ampImage.drawAt(g, 338, 69, 1.0f);
    cutoffImage.drawAt(g, 212, 220, 1.0f);
    resImage.drawAt(g, 268, 220, 1.0f);
    aImage.drawAt(g, 350, 220, 1.0f);
    dImage.drawAt(g, 395, 220, 1.0f);
    sImage.drawAt(g, 442, 220, 1.0f);
    rImage.drawAt(g, 489, 220, 1.0f);
    gainImage.drawAt(g, 523, 220, 1.0f);
    
    g.setFont (16.0f);
}

void StocSynthAudioProcessorEditor::resized()
{
    // Won't happen
}

void StocSynthAudioProcessorEditor::comboBoxChanged(ComboBox *comboBox) {
    if(comboBox == &wavebox) {
        processor.setParameterNotifyingHost (StocSynthAudioProcessor::WAVE_PARAM,
                                             comboBox->getSelectedId());
        
        repaint();
    }
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