/*
  ==============================================================================

    SynthOscillator.cpp
    Created: 28 Aug 2020 2:36:12pm
    Author:  Jackson, Judith

  ==============================================================================
*/

#include "SynthOscillator.h"
#include <cmath>
#include <JuceHeader.h>

float SynthOscillator::getSample() //will need to have input wavetable param
{
    float sample = 0.0f;
    sample = (float)(std::sin(currentAngle * 2.0 * juce::double_Pi)); //refactor to be a call to wavetable
    currentAngle += angleDelta;
    while (currentAngle > 1.0) currentAngle -= 1.0; //for wrapping, will be different w/ wavetable
    
    return sample;
}
