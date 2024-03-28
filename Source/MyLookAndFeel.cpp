/*
  ==============================================================================

    MyLookAndFeel.cpp
    Created: 26 Feb 2024 10:15:24pm
    Author:  Joshua Cann

  ==============================================================================
*/

#include "MyLookAndFeel.h"

MyLookAndFeel::MyLookAndFeel(){}

MyLookAndFeel::~MyLookAndFeel(){}

void MyLookAndFeel::drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&)
{
    auto radius = (float) juce::jmin (width / 2, height / 2) * 0.925f;
    auto centreX = (float) x + (float) width  * 0.5f;
    auto centreY = (float) y + (float) height * 0.5f;
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    auto rw = radius * 2.0f;
    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    
    // fill
    g.setColour (juce::Colours::transparentBlack);
    g.fillEllipse (rx, ry, rw, rw);

    // outline
    g.setColour (juce::Colours::lightsteelblue);
    g.drawEllipse (rx, ry, rw, rw, 2.0f);
    
    // sets pointer
    juce::Path p;
    auto pointerLength = radius * 0.5f;
    auto pointerThickness = 5.0f;
    p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
    p.applyTransform (juce::AffineTransform::rotation (angle).translated (centreX, centreY));
    
    // sets level
    Path l;
    l.startNewSubPath(centreX * 0.5, centreY * 1.75);
    l.addCentredArc(centreX, centreY, radius, radius, 0, rotaryStartAngle, angle);
    
    // paints pointer
    g.setColour(Colours::blueviolet);
    g.strokePath (l, PathStrokeType(3.0f));
    
    // paints level indicator
    g.setColour (juce::Colours::white);
    g.fillPath (p);
}
