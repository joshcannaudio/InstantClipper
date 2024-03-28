/*
  ==============================================================================

    MyLookAndFeel.h
    Created: 26 Feb 2024 10:15:24pm
    Author:  Joshua Cann

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class MyLookAndFeel : public juce::LookAndFeel_V4 {
public:
    MyLookAndFeel();
    
    ~MyLookAndFeel();
    
    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                           const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) override;
private:
    
};
