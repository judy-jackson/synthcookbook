/*
  ==============================================================================

    SynthWaveform.h
    Created: 10 Sep 2020 3:54:07pm
    Author:  Jackson, Judith

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SynthWaveform
{
private:
    enum WaveformTypeIndex {
        kSine, kTriangle, kSquare, kSawtooth,
        kNumberOfWaveformTypes
    } index;
    
    friend class SynthWavetableOscillator;
    
public:
    // default constructor
    //SynthWaveform() : index(kSine) {}
    //SynthWaveform() : index(kSquare) {}
    SynthWaveform() : index(kSawtooth) {}
    //SynthWaveform() : index(kTriangle) {}
    
    // set to default state after construction
    void setToDefault() { index = kSine; }
    
    
    // serialize: get human-readable name of this waveform
    juce::String name();
    
    // deserialize: set index based on given name
    void setFromName(juce::String wfName);
    
private:
    // waveform names: ordered list of string literals
    static const char* const wfNames[];
};
