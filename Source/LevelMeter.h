/*
  ==============================================================================

    LevelMeter.h
    Created: 23 Feb 2024 11:23:38am
    Author:  Joshua Cann

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

//namespace Gui
//{
class LevelMeter : public juce::Component
{
public:
    LevelMeter();
    
    ~LevelMeter();
    
    void paint(Graphics& g) override;
    
    void setLevel(const float value);
    
    float getLevel();
    
private:
    float level = -60.f;
};
//}
