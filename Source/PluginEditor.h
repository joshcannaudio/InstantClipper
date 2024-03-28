/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Clipper.h"
#include "MySlider.h"
#include "MyLabel.h"
#include "LevelMeter.h"

#define NUM_SLIDERS 5

//==============================================================================
/**
*/
class ClipperAudioProcessorEditor  : public juce::AudioProcessorEditor, public Timer
{
public:
    ClipperAudioProcessorEditor (ClipperAudioProcessor&);
    ~ClipperAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    //==============================================================================
    void timerCallback() override;
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Image pluginBackground;
    
    ClipperAudioProcessor& audioProcessor;
    MySlider mySlider[NUM_SLIDERS];
    
    Label label[NUM_SLIDERS];
    
    LevelMeter levelMeterL, levelMeterR;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ClipperAudioProcessorEditor)
};
