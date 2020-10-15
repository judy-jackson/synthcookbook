/*
  ==============================================================================

    SynthWavetableOscillator.cpp
    Created: 2 Sep 2020 12:34:57pm
    Author:  Jackson, Judith

  ==============================================================================
*/

#include "SynthWavetableOscillator.h"

void SynthWavetableOscillator::initializeWavetable()
{
    currentTable = wavetables.getTable(waveform, 0.8);
    //wavetables.printTable(currentTable);
}


float SynthWavetableOscillator::getSample()
{
    int intIndex = (unsigned int) currentIndex;
    float* table = currentTable.table;
    auto index0 = table + intIndex;
    auto index1 = index0 + 1;
    
    float frac = (table + intIndex) - index0;
    float currentSample = *index0 + frac * ((*index1) - (*index0));
    juce::Logger::getCurrentLogger()->writeToLog((juce::String) currentSample);
    
    if ((currentIndex += tableDelta) > (float) tableSize)  
        currentIndex -= (float) tableSize;
        return currentSample;
}
