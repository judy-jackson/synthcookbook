/*
  ==============================================================================

    SynthWavetableOscillator.cpp
    Created: 2 Sep 2020 12:34:57pm
    Author:  Jackson, Judith

  ==============================================================================
*/

#include "SynthWavetableOscillator.h"

float SynthWavetableOscillator::sineTable[tableSize + 1];
float SynthWavetableOscillator::squareTable[tableSize + 1];
float SynthWavetableOscillator::sawTable[tableSize + 1];
float SynthWavetableOscillator::triTable[tableSize + 1];

void SynthWavetableOscillator::initializeWavetable()
{    
    auto tableDelta = juce::MathConstants<double>::twoPi / (double) (tableSize - 1);
    auto tableAngle = 0.0;
    
    for (unsigned int i = 0; i < tableSize; ++i)
    {
        //auto sample = std::sin (tableAngle);
        //sineTable[i] = (float) sample;
        sineTable[i] = (float) std::sin (tableAngle);
        sawTable[i] = (float) (2.0 * tableAngle - 1.0);
        squareTable[i] = (tableAngle <= 0.5) ? 1.0f : -1.0f;
        triTable[i] = (2.0 * (0.5 - std::fabs(tableAngle - 0.5)) - 1.0);;
        tableAngle += tableDelta;
    }
    
    sineTable[tableSize] = sineTable[0];
    sawTable[tableSize] = sawTable[0];
    squareTable[tableSize] = squareTable[0];
    triTable[tableSize] = triTable[0];
}

float SynthWavetableOscillator::getSample()
{
    auto index0 = (unsigned int) currentIndex;
    auto index1 = index0 + 1;
    //auto value0 = 0;
    //auto value1 = 0;
    //auto value0 = sineTable[index0];
    //auto value1 = sineTable[index1];
    float value0;
    float value1;
    
    switch (waveform.index)
    {
        case SynthWaveform::kSine:
            //get sine table
            juce::Logger::getCurrentLogger()->writeToLog("Sine waveform");
            value0 = sineTable[index0];
            value1 = sineTable[index1];
            break;
            
        case SynthWaveform::kSquare:
            juce::Logger::getCurrentLogger()->writeToLog("Square waveform");
            value0 = squareTable[index0];
            value1 = squareTable[index1];
            juce::Logger::getCurrentLogger()->writeToLog((juce::String) value0);
            break;
            
        case SynthWaveform::kSawtooth:
            juce::Logger::getCurrentLogger()->writeToLog("Sawtooth waveform");
            value0 = sawTable[index0];
            value1 = sawTable[index1];
            break;
            
        case SynthWaveform::kTriangle:
            juce::Logger::getCurrentLogger()->writeToLog("Triangle waveform");
            value0 = triTable[index0];
            value1 = triTable[index1];
            break;
    }
    
    auto frac = currentIndex - (float) index0;
    auto currentSample = value0 + frac * (value1 - value0);
    juce::Logger::getCurrentLogger()->writeToLog((juce::String) currentSample);
    
    if ((currentIndex += tableDelta) > (float) tableSize)  
        currentIndex -= (float) tableSize;
        
        return currentSample;
}
