/*
  ==============================================================================

    SynthEnvelopeGenerator.h
    Created: 26 Aug 2020 5:15:10pm
    Author:  Jackson, Judith

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SynthEnvelopeGenerator
{
private:
    double sampleRateHz;
    juce::SmoothedValue<double> interpolator;
    
    enum class EG_Segment
    {
        idle,
        attack,
        decay,
        sustain,
        release
    } segment;
    
public:
    double attackSeconds, decaySeconds, releaseSeconds;
    double sustainLevel;    // [0.0, 1.0]
    
public:
    SynthEnvelopeGenerator();
    
    void start(double _sampleRateHz);   // called for note-on
    void release();                     // called for note-off
    bool isRunning() { return segment != EG_Segment::idle; }
    float getSample ();
};
