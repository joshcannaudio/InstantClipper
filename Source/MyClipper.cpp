/*
  ==============================================================================

    MyClipper.cpp
    Created: 22 Feb 2024 4:11:54pm
    Author:  Joshua Cann

  ==============================================================================
*/

#include "MyClipper.h"

MyClipper::MyClipper()
{
    drive_ = 0;
    threshold_ = 0;
    aCoeff_ = 0;
}

MyClipper::~MyClipper()
{
    
}

float MyClipper::getSmoothGainControl(float inputSample)
{
    return inputSample * inputSample * inputSample;
}

void MyClipper::setClipper(float drive, float threshold, float aCoeff, ClipType clipType)
{
    drive_ = drive;
    threshold_ = threshold;
    aCoeff_ = aCoeff;
    clipType_ = clipType;
    
    if(clipType == 0)
        drive_ = drive_ * 0.04 + 1;
    if(clipType == 1)
        drive_ = drive * 0.09 + 1;
//        drive_ = drive * 0.015 + 1;
}

float MyClipper::clip(float inputSample)
{
    switch (int(clipType_)) {
        case HARD:
            return getHardClip(inputSample);
            break;
        case SOFT:
            return getSoftClip(inputSample);
            break;
        case CIRCLE:
            return getCircle(inputSample);
        default:
            return 0;
            break;
    }
}

float MyClipper::getHardClip(float inputSample)
{
    float clippedSample = inputSample * drive_;
    
    if(clippedSample >= threshold_)
        clippedSample = threshold_;
    else if(clippedSample <= -threshold_)
        clippedSample = -threshold_;
    
    return clippedSample;
}

float MyClipper::getSoftClip(float inputSample)
{
    float clippedSample = inputSample * drive_;
    float k = 2 + (drive_ * 0.3);
                                                                                    // changing 1 makes for nice effects
    clippedSample = signum(clippedSample) * std::pow(std::atan(std::pow(abs(clippedSample), k)), (1.0f / k));
    return clippedSample;
}

float MyClipper::getCircle(float inputSample)
{
    if(inputSample > 0)
        return sqrt(threshold_ - juce::square(inputSample - 1));
    else
        return sqrt(-threshold_ + juce::square(inputSample + 1));
}

float MyClipper::getQuatisation(float inputSample, float drive)
{
    int truncate;
    drive = drive * 14.0 + 1.0;
    inputSample *= drive;
    truncate = inputSample;
    inputSample = truncate / 5.0;
    return inputSample;
}

float MyClipper::getFolding(float inputSample, float drive)
{
    drive = drive * 4.0 + 1.0;
    inputSample *= drive;
   
    if(inputSample >= 1)
       inputSample = -drive / 2.0 + 1.0;
    if(inputSample <= -1)
        inputSample = -drive / 2.0 - 2.0;
    
    if(inputSample > 1)
        inputSample = 1;
    if(inputSample < -1)
        inputSample = -1;
    
    return inputSample;
}

float MyClipper::getAsymmetric(float inputSample, float drive, float cCoeff)
{
    drive = drive * 4.0 + 1.0;
    inputSample *= drive;
    
    cCoeff *= 0.9;
    cCoeff = 1 + 1 * cCoeff;
    
    float aCoeff = 1.0 / cCoeff + 1.0;
    
    if (inputSample < 0)
       inputSample = inputSample + pow((-inputSample), aCoeff) / aCoeff;
    if(inputSample > 0 && inputSample <= 1)
       inputSample = inputSample;
    if(inputSample > 1)
        inputSample = 1;
    
    return inputSample;
}
