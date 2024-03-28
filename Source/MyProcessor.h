/*
  ==============================================================================

    MyProcessor.h
    Created: 22 Feb 2024 3:27:51pm
    Author:  Joshua Cann

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "MyClipper.h"
#include "Clipper.h"

class MyProcessor {
public:
    MyProcessor();
    
    ~MyProcessor();
    
    void prepareToPlay(double currentSampleRate);
    
    void process(const float *pfInBuffer0, const float *pfInBuffer1, float *pfOutBuffer0, float *pfOutBuffer1, int numSamples, juce::AudioProcessorValueTreeState& apvts, juce::AudioBuffer<float>& buffer);
    
private:
    double sampleRate = 44100.f;
    MyClipper clipper;
    Clipper myFunctions;
    
//    enum ClipType { HARD, SOFT, CIRCLE };
//    ClipType clipType;
};
