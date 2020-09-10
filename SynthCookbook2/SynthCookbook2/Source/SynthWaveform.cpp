/*
  ==============================================================================

    SynthWaveform.cpp
    Created: 10 Sep 2020 3:54:07pm
    Author:  Jackson, Judith

  ==============================================================================
*/

#include "SynthWaveform.h"

const char* const SynthWaveform::wfNames[] = {
    "Sine", "Triangle", "Square", "Sawtooth"
};

void SynthWaveform::setFromName(juce::String wfName)
{
    for (int i = 0; i < kNumberOfWaveformTypes; i++)
    {
        if (wfName == wfNames[i])
        {
            index = (WaveformTypeIndex)i;
            return;
        }
    }
    
    // Were we given an invalid waveform name?
    jassertfalse;
}

juce::String SynthWaveform::name()
{
    return wfNames[index];
}
