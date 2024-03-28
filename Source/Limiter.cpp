/*
  ==============================================================================

    Limiter.cpp
    Created: 22 Feb 2024 9:59:47pm
    Author:  Joshua Cann

  ==============================================================================
*/

#include "Limiter.h"

Limiter::Limiter()
{
    
}

Limiter::~Limiter()
{
    
}

void Limiter::setLimiter(float attackTime, float releaseTime, float inputGain, float drive, float threshold, float outputGain, double sampleRate)
{
    sampleRate_ = sampleRate;
    
    attackTime_ = inv(attackTime) / sampleRate_;
    releaseTime_ = inv(releaseTime) / sampleRate_;
    inputGain_ = inputGain;
    drive_ = drive;
    threshold_ = threshold;
    outputGain_ = outputGain;
}

float Limiter::tick(float inputSample)
{
    if(inputSample > threshold_)
        stage = ATTACK;
    else if(inputSample == threshold_)
        stage = HOLD;
    else if(inputSample < threshold_)
        stage = RELEASE;
    
    switch (stage) {
        case ATTACK:
            inputSample -= attackTime_;
            break;
        case HOLD:
            inputSample = threshold_;
        case RELEASE:
            inputSample -= releaseTime_;
        default:
            break;
    }
    
    return 0;
}
