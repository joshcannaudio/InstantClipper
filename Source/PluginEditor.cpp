/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ClipperAudioProcessorEditor::ClipperAudioProcessorEditor (ClipperAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (600, 300);
    
    pluginBackground = ImageCache::getFromMemory (BinaryData::Figma_Plugin_Background_png, BinaryData::Figma_Plugin_Background_pngSize);
    
    Font myFont;
    myFont.setSizeAndStyle(20, 1, 1.0f, 0.0f);
    
    for(int i = 0; i < NUM_SLIDERS; i++) {
        String parameterID = "Parameter";
        String appendix = std::to_string(i + 1);
        parameterID = parameterID << appendix;
        DBG(parameterID);
        mySlider[i].createSlider(parameterID, audioProcessor.apvts);
        addAndMakeVisible(mySlider[i]);
        
        addAndMakeVisible(label[i]);
        label[i].setJustificationType(Justification::centred);
        label[i].setBorderSize(BorderSize<int>());
        label[i].setFont(myFont);
    }
    
//    addAndMakeVisible(levelMeterL);
//    addAndMakeVisible(levelMeterR);
//
//    addAndMakeVisible(audioProcessor.audioVisualiser);
    
    startTimerHz(24);
}

ClipperAudioProcessorEditor::~ClipperAudioProcessorEditor()
{
}

//==============================================================================
void ClipperAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour (juce::Colours::white);
    
    g.drawImage(pluginBackground, getLocalBounds().toFloat());
    
    // overrides slider style
//    mySlider[2].slider.setSliderStyle(Slider::SliderStyle::LinearVertical);
//    mySlider[3].slider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    
    // x y width height (600, 300)
    /// set size of slider and location that it will render
    // Input Gain (-inf -> +6db)
    mySlider[0].setBounds(getWidth() * 0.025, getHeight() * 0.6, getWidth() * 0.125, getHeight() * 0.25);
//    mySlider[0].slider.setTextValueSuffix("dB");
    
    // Drive (0 -> 100%)
    mySlider[1].setBounds(getWidth() * 0.2, getHeight() * 0.3, getWidth() * 0.2, getHeight() * 0.4);
//    mySlider[1].slider.setTextValueSuffix("%");
    
    // Clip Threshold (0 -> -inf)
    mySlider[2].setBounds(getWidth() * 0.6, getHeight() * 0.3, getWidth() * 0.2, getHeight() * 0.4);
//    mySlider[2].slider.setTextValueSuffix("dB");
    
    // Output Gain (-inf -> +6db)
    mySlider[3].setBounds(getWidth() * 0.85, getHeight() * 0.6, getWidth() * 0.125, getHeight() * 0.25);
//    mySlider[3].slider.setTextValueSuffix("dB");
    
    mySlider[4].setBounds(getWidth() * 0.45, getHeight() * 0.7, getWidth() * 0.1, getHeight() * 0.2);
    
//    mySlider[5].setBounds(getWidth() * 0.05, getHeight() * 0.1, getWidth() * 0.1375, getWidth() * 0.18333);
    
    // Display values of plugins
    for(int i = 0; i < 4; i++) { // all but distortion type
        label[i].setColour(juce::Label::backgroundColourId, Colours::transparentBlack);
        label[i].setBounds(mySlider[i].getX(), mySlider[i].getBottom() - (getHeight() * 0.03), mySlider[i].getWidth(), getHeight() * 0.1);
    }
    
    label[5].setColour(juce::Label::backgroundColourId, Colours::transparentBlack);
    label[5].setBounds(mySlider[5].getX(), mySlider[5].getBottom() - (getHeight() * 0.03), mySlider[5].getWidth(), getHeight() * 0.1);
    
    // draw oscillator
}

void ClipperAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    levelMeterL.setBounds(getWidth() * 0.83, getHeight() * 0.18, getWidth() * 0.05, getHeight() * 0.417);
    levelMeterR.setBounds(getWidth() * 0.9, getHeight() * 0.18, getWidth() * 0.05, getHeight() * 0.417);
    
    audioProcessor.audioVisualiser.setColours(Colours::transparentWhite, Colours::white);
    audioProcessor.audioVisualiser.setBounds(getWidth() * 0.25, getHeight() * 0.1666, getWidth() * 0.5, getHeight() * 0.41666);
}

void ClipperAudioProcessorEditor::timerCallback()
{
    for(int i = 0; i < NUM_SLIDERS; i++) {
        String suffix[NUM_SLIDERS] = { "dB", "%", "dB", "dB" };
        label[i].setText(mySlider[i].slider.getTextFromValue(mySlider[i].slider.getValue()) + suffix[i], NotificationType::dontSendNotification);
        label[i].repaint();
    }
    
    levelMeterL.setLevel(audioProcessor.getRmsValue(0));
    levelMeterR.setLevel(audioProcessor.getRmsValue(1));
    
    levelMeterL.repaint();
    levelMeterR.repaint();
}

/* To Do
 1. Add level values to meters
 2. make oscillascope more like oscillascope
 3. fill space on left?
 4. look into adding graphic design elements to level meters
*/
