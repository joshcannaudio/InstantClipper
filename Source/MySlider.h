/*
  ==============================================================================

    MySlider.h
    Created: 22 Feb 2024 4:36:51pm
    Author:  Joshua Cann

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Clipper.h"
#include "MyLookAndFeel.h"

class MySlider : public Component {
public:
    MySlider();
    
    ~MySlider();
    
    void createSlider(String SliderID, AudioProcessorValueTreeState& apvts);
    
    void mouseDrag(const MouseEvent &event) override;
    
    void paint(Graphics& g) override;
    
    Slider slider;
private:
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderAttachment;
    MyLookAndFeel myLookAndFeel;
};
