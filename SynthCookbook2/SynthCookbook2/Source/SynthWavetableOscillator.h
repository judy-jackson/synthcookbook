/*
  ==============================================================================

    SynthWavetableOscillator.h
    Created: 2 Sep 2020 12:34:57pm
    Author:  Jackson, Judith

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SynthWavetableOscillator
{
private:
    //SynthWaveform waveform;
    float currentIndex = 0.0f, tableDelta = 0.0f;
    static const unsigned int tableSize = 1 << 7;
    
public:
    //constructor initializes currentAngle, angleDelta
    SynthWavetableOscillator() : currentIndex(0), tableDelta(0) {}
    
    static void initializeWavetable();
    
    //void setWaveform(SynthWaveform wf) { waveform = wf; }
    void resetCurrentAngle() { currentIndex = 0; }
    void setFrequency(double cyclesPerSample) { tableDelta = (cyclesPerSample * tableSize); }
    
    float getSample();
    float getLevel() {return 0.8;}
    
    static float sineTable[tableSize];
    
};
