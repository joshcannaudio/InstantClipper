/*
  ==============================================================================

    Limiter.h
    Created: 22 Feb 2024 9:59:47pm
    Author:  Joshua Cann

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Clipper.h"

class Limiter {
public:
    Limiter();
    
    ~Limiter();
    
    void setLimiter(float attackTime, float releaseTime, float inputGain, float drive, float threshold, float outputGain, double sampleRate);
    
    float tick(float inputSample);
    
    enum STAGE {
        ATTACK,
        HOLD,
        RELEASE,
        OFF
    };
    
private:
    float attackTime_, releaseTime_, inputGain_, drive_, threshold_, outputGain_, amplitude = 0;
    double sampleRate_ = 44100;
    STAGE stage;
    float inv(float val) { return 1.0 / val; }
};
