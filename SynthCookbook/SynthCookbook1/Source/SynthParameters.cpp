/*
  ==============================================================================

    SynthParameters.cpp
    Created: 26 Aug 2020 4:19:23pm
    Author:  Jackson, Judith

  ==============================================================================
*/

#include "SynthParameters.h"

void SynthParameters::setDefaultValues()
{
    programName = "Default";
    masterLevel = 0.15f;
    oscBlend= 0.5f;
    pitchBendUpSemitones = 2;
    pitchBendDownSemitones = 2;
    //osc1Waveform.setToDefault();
    osc1PitchOffsetSemitones = 0;
    osc1DetuneOffsetCents = -10.0f;
    //osc2Waveform.setToDefault();
    osc2PitchOffsetSemitones = 0;
    osc2DetuneOffsetCents = +10.0f;
    ampEgAttackTimeSeconds = 0.1f;
    ampEgDecayTimeSeconds = 0.1f;
    ampEgSustainLevel = 0.8f;
    ampEgReleaseTimeSeconds = 0.5f;
}
