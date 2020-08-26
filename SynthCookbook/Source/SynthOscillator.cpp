/*
  ==============================================================================

    SynthOscillator.cpp
    Created: 26 Aug 2020 4:18:58pm
    Author:  Jackson, Judith

  ==============================================================================
*/
#include "SynthOscillator.h"
#include <cmath>
#include <JuceHeader.h>

float SynthOscillator::getSample() //will need to have input wavetable param
{
    float sample = 0.0f;
    sample = (float)(std::sin(phase * 2.0 * juce::double_Pi)); //refactor to be a call to wavetable
    phase += phaseDelta;
    while (phase > 1.0) phase -= 1.0; //for wrapping, will be different w/ wavetable
    
    return sample;
}
