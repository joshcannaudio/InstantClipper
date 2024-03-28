/*
  ==============================================================================

    Clipper.h
    Created: 22 Feb 2024 4:38:35pm
    Author:  Joshua Cann

  ==============================================================================
*/

#pragma once
using namespace juce;

class Clipper {
public:
    /** Converts amplitude to dB */
    float amplitudeTodB(float amplitude)
    {
        return 20 * log10(amplitude);
    }

    /** Converts dB to amplitude */
    float dBtoAmplitude(float dB)
    {
        float amplitude = pow(10, dB / 20);
            if(dB <= -60)
                amplitude = 0;
            return amplitude;
    }
    
    void setSampleRate(double currentSampleRate)
    {
        sampleRate = currentSampleRate;
    }
    
    float getSampleRate()
    {
        return sampleRate;
    }
    
private:
    double sampleRate = 44100;
};
