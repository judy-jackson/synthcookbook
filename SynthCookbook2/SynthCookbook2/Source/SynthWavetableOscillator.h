/*
  ==============================================================================

    SynthWavetableOscillator.h
    Created: 2 Sep 2020 12:34:57pm
    Author:  Jackson, Judith

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthWaveform.h"
#include "SynthWavetable.h"

class SynthWavetableOscillator
{
private:
    
    wavetable currentTable;
    float currentIndex = 0.0f, tableDelta = 0.0f;
    static const unsigned int tableSize = (1 << 10) - 1;
    
public:
    //constructor initializes currentAngle, angleDelta
    SynthWavetableOscillator() : currentIndex(0), tableDelta(0) { initializeWavetable(); }
    
    void initializeWavetable();
    
    //void setWaveform(SynthWaveform wf) { waveform = wf; }
    void resetCurrentAngle() { currentIndex = 0; }
    
    //refactor to include table selection based off frequency
    void setFrequency(double cyclesPerSample) { tableDelta = (cyclesPerSample * tableSize); }
    
    //add setWaveform when app becomes dynamic, include table selection
    
    float getSample();
    float getLevel() {return 0.8;}
    
    SynthWavetable wavetables;
    SynthWaveform waveform;
    
};
