/*
  ==============================================================================

    LevelMeter.cpp
    Created: 23 Feb 2024 11:23:38am
    Author:  Joshua Cann

  ==============================================================================
*/

#include "LevelMeter.h"

LevelMeter::LevelMeter(){}

LevelMeter::~LevelMeter(){}

void LevelMeter::paint(Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();
    
    g.setColour(Colours::white.withBrightness(0.4));
    g.fillRoundedRectangle(bounds, 5.f);
    
    if(Decibels::gainToDecibels(level) < -12.0f)
        g.setColour(Colours::green);
    if(Decibels::gainToDecibels(level) > -12.0f)
        g.setColour(Colours::greenyellow);
    if(Decibels::gainToDecibels(level) > 0.0f)
        g.setColour(Colours::red);
    
    const auto scaledY =
        jmap(level, -60.f, +6.f, 0.f, static_cast<float>(getHeight()));
    
    g.fillRoundedRectangle(bounds.removeFromBottom(scaledY), 5.f);
}

void LevelMeter::setLevel(const float value) { level = value; }

float LevelMeter::getLevel() { return level; }
