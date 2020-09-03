/*
  ==============================================================================

    SynthWavetableOscillator.cpp
    Created: 2 Sep 2020 12:34:57pm
    Author:  Jackson, Judith

  ==============================================================================
*/

#include "SynthWavetableOscillator.h"

float SynthWavetableOscillator::sineTable[tableSize];

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
}

forcedinline float SynthWavetableOscillator::getSample() noexcept
{
    //auto tableSize = (unsigned int) wavetable.getNumSamples();
    
    auto index0 = (unsigned int) currentIndex;              // [6]
    auto index1 = index0 == (tableSize - 1) ? (unsigned int) 0 : index0 + 1;
    
    auto frac = currentIndex - (float) index0;              // [7]
    
    //auto* table = wavetable.getReadPointer (0);             // [8]
    auto value0 = sineTable[index0];
    auto value1 = sineTable[index1];
    
    auto currentSample = value0 + frac * (value1 - value0); // [9]
    
    if ((currentIndex += tableDelta) > (float) tableSize)   // [10]
        currentIndex -= (float) tableSize;
        
        return currentSample;
}
