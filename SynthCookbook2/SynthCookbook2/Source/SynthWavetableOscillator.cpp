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
    //printf("Initializing wavetable");
    currentTable = wavetables.getTable(waveform, 100.0);
}

void SynthWavetableOscillator::setFrequency(double cyclesPerSample, double frequency) //maybe pass in hz value initally and convert to delta in this function
{
    juce::String out1;
    out1 << "Frequency (CPS) in SynthOscillator: " << cyclesPerSample << "\n";
    juce::Logger::getCurrentLogger()->writeToLog(out1);
    if ((frequency < currentTable->lowestFreq) || (frequency > currentTable->highestFreq)){
        currentTable = wavetables.getTable(waveform, frequency);
        juce::String out;
        out << "Frequency (Hz) in SynthOscillator: " << frequency <<"\n";
        out << "Current table lowest freq: " << currentTable->lowestFreq << "\n";
        out << "Current table highest freq: " << currentTable->highestFreq << "\n";
        out << "Current table size: " << currentTable->size << "\n";
        out << "Value at first table index: " << *(currentTable->table) << "\n";
        juce::Logger::getCurrentLogger()->writeToLog(out);
    }
    //tableDelta = (cyclesPerSample * tableSize); //change this to currentTable.size
    tableDelta = (cyclesPerSample * currentTable->size);
}


float SynthWavetableOscillator::getSample()
{
    int intIndex = (unsigned int) currentIndex;
    float* table = currentTable->table; 
    auto index0 = table + intIndex;
    auto index1 = index0 + 1;
    juce::String out;
    out << "Index 0: " << *index0 << "\n";
    out << "Index 1: " << *index1 << "\n";
    
    float frac = (table + intIndex) - index0;
    float currentSample = *index0 + frac * ((*index1) - (*index0));
    juce::Logger::getCurrentLogger()->writeToLog((juce::String) currentSample);
    
    if ((currentIndex += tableDelta) > (float) currentTable->size) {
        currentIndex -= (float) currentTable->size;
    }
    return currentSample;
}
