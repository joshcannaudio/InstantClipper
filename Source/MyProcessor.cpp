/*
  ==============================================================================

    MyProcessor.cpp
    Created: 22 Feb 2024 3:27:51pm
    Author:  Joshua Cann

  ==============================================================================
*/

#include "MyProcessor.h"

MyProcessor::MyProcessor()
{
    
}

MyProcessor::~MyProcessor()
{
    
}

void MyProcessor::prepareToPlay(double currentSampleRate)
{
    sampleRate = currentSampleRate;
}

void MyProcessor::process(const float *pfInBuffer0, const float *pfInBuffer1, float *pfOutBuffer0, float *pfOutBuffer1, int numSamples, juce::AudioProcessorValueTreeState& apvts, juce::AudioBuffer<float>& buffer)
{
    float fIn0, fIn1, fOut0 = 0, fOut1 = 0;
    
    // Load parameters and store to variable
    float drive = apvts.getRawParameterValue("Parameter2")->load();
    float threshold = apvts.getRawParameterValue("Parameter3")->load();
    
    int clipType = apvts.getRawParameterValue("Parameter5")->load();
    float coeff = apvts.getRawParameterValue("Parameter6")->load();
    
    //Process variables before being passed to functions
//    drive = (drive * 0.04) + 1; // input gain will be displayed as a percentage
    threshold = Decibels::decibelsToGain(threshold);
    coeff = coeff;
    
    // sets all variables in clipper object
    clipper.setClipper(drive, threshold, coeff, (MyClipper::ClipType)clipType);
    
    
    
    for(int sample = 0; sample < numSamples; ++sample)
    {
        fIn0 = pfInBuffer0[sample];
        fIn1 = pfInBuffer1[sample];

        fOut0 = clipper.clip(fIn0);
        fOut1 = clipper.clip(fIn1);
        
//        fOut0 = clipper.getSoftClip(fIn0);
//        fOut1 = clipper.getSoftClip(fIn1);
        
//        fOut0 = fIn0;
//        fOut1 = fIn1;
        
        ++pfOutBuffer0[sample] = fOut0;
        ++pfOutBuffer1[sample] = fOut1;
    }
}

