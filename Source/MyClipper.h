/*
  ==============================================================================

    MyClipper.h
    Created: 22 Feb 2024 4:11:54pm
    Author:  Joshua Cann

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class MyClipper {
public:
    enum ClipType { HARD = 0, SOFT, CIRCLE };
    MyClipper();
    
    ~MyClipper();
    
    float getSmoothGainControl(float input);
    
    void setClipper(float drive, float threshold, float aCoeff, ClipType clipType);
    
    float clip(float inputSample);
    
protected:
    float getHardClip(float inputSample);

    float getSoftClip(float inputSample);

    float getQuatisation(float inputSample, float drive);

    float getFolding(float inputSample, float drive);

    float getAsymmetric(float inputSample, float drive, float cCoeff);

    float getCircle(float inputSample);
    
private:
    ClipType clipType_;
//    float drive_ = 0, threshold_ = 0, aCoeff_ = 0;
    float drive_, threshold_, aCoeff_;
    float cube(float num) { return num * num * num; }
    
    inline double fastatan( double x )
    {
        return (x / (1.0 + 0.28 * (x * x)));
    }
    
    float signum(float num)
    {
        if(num > 0)
            return threshold_;
        else
            return -threshold_;
    }
};
