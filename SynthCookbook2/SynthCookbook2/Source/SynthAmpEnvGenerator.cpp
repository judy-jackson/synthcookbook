/*
  ==============================================================================

    SynthAmpEnvGenerator.cpp
    Created: 4 Sep 2020 12:28:20pm
    Author:  Jackson, Judith

  ==============================================================================
*/

#include "SynthAmpEnvGenerator.h"

SynthAmpEnvGenerator::SynthAmpEnvGenerator()
    : sampleRateHz(44100)
    , segment(EG_Segment::idle)
    , attackSeconds(0.01)
    , decaySeconds(0.1)
    , releaseSeconds(0.5)
    , sustainLevel(0.5)
{
    interpolator.setCurrentAndTargetValue(0.0);
    interpolator.reset(sampleRateHz, 0.0);
}

void SynthAmpEnvGenerator::start (double _sampleRateHz)
{
    sampleRateHz = _sampleRateHz;
    
    if (segment == EG_Segment::idle)
    {
        // start new attack segment from zero
        interpolator.setCurrentAndTargetValue(0.0);
        interpolator.reset(sampleRateHz, attackSeconds);
    }
    else
    {
        // note is still playing but has been retriggered or stolen
        // start new attack from where we are
        double currentValue = interpolator.getNextValue();
        interpolator.setTargetValue(currentValue);
        interpolator.reset(sampleRateHz, attackSeconds * (1.0 - currentValue));
    }
    
    segment = EG_Segment::attack;
    interpolator.setTargetValue(1.0);
}

void SynthAmpEnvGenerator::release()
{
    segment = EG_Segment::release;
    interpolator.setTargetValue(interpolator.getNextValue());
    interpolator.reset(sampleRateHz, releaseSeconds);
    interpolator.setTargetValue(0.0);
}

float SynthAmpEnvGenerator::getSample()
{
    //clean up conditionals (leverage enum for a switch?)
    if (segment == EG_Segment::sustain) return float(sustainLevel);
    
    if (interpolator.isSmoothing()) return float(interpolator.getNextValue());
    
    if (segment == EG_Segment::attack)    // end of attack segment
    {
        if (decaySeconds > 0.0)
        {
            // there is a decay segment
            segment = EG_Segment::decay;
            interpolator.reset(sampleRateHz, decaySeconds);
            interpolator.setTargetValue(sustainLevel);
            return 1.0;
        }
        else
        {
            // no decay segment; go straight to sustain
            segment = EG_Segment::sustain;
            return float(sustainLevel);
        }
    }
    else if (segment == EG_Segment::decay)    // end of decay segment
    {
        segment = EG_Segment::sustain;
        return float(sustainLevel);
    }
    else if (segment == EG_Segment::release)    // end of release
    {
        segment = EG_Segment::idle;
    }
    
    // after end of release segment
    return 0.0f;
}
