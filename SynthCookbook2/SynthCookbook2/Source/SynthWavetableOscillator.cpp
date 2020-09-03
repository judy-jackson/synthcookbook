/*
  ==============================================================================

    SynthWavetableOscillator.cpp
    Created: 2 Sep 2020 12:34:57pm
    Author:  Jackson, Judith

  ==============================================================================
*/

#include "SynthWavetableOscillator.h"

float SynthWavetableOscillator::sineTable[tableSize + 1];

void SynthWavetableOscillator::initializeWavetable()
{    
    auto tableDelta = juce::MathConstants<double>::twoPi / (double) (tableSize - 1);
    auto tableAngle = 0.0;
    
    for (unsigned int i = 0; i < tableSize; ++i)
    {
        auto sample = std::sin (tableAngle);
        sineTable[i] = (float) sample;
        tableAngle += tableDelta;
    }
    
    sineTable[tableSize] = sineTable[0];
}

float SynthWavetableOscillator::getSample()
{
    auto index0 = (unsigned int) currentIndex;
    auto index1 = index0 + 1;
    
    auto frac = currentIndex - (float) index0;
    
    auto value0 = sineTable[index0];
    auto value1 = sineTable[index1];
    
    auto currentSample = value0 + frac * (value1 - value0);
    
    if ((currentIndex += tableDelta) > (float) tableSize)  
        currentIndex -= (float) tableSize;
        
        return currentSample;
}
