/*
  ==============================================================================

    MySlider.cpp
    Created: 22 Feb 2024 4:36:51pm
    Author:  Joshua Cann

  ==============================================================================
*/

#include "MySlider.h"

MySlider::MySlider()
{
    addMouseListener(this, true);
    addAndMakeVisible(slider);
    slider.setLookAndFeel(&myLookAndFeel);
}

MySlider::~MySlider()
{
    
}

void MySlider::createSlider(String SliderID, AudioProcessorValueTreeState& apvts)
{
    
    // sets slider
    slider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    
    sliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(apvts, SliderID, slider);
}

void MySlider::mouseDrag(const MouseEvent &event)
{
    repaint();
}

void MySlider::paint(Graphics& g)
{
    slider.setBounds(getLocalBounds());
}
