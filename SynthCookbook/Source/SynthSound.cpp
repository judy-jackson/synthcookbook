/*
  ==============================================================================

    SynthSound.cpp
    Created: 26 Aug 2020 4:19:36pm
    Author:  Jackson, Judith

  ==============================================================================
*/

#include "SynthSound.h"
#include "Synth.h"

SynthSound::SynthSound(Synth& ownerSynth)
: SynthesiserSound()
, synth(ownerSynth)
{
}

void SynthSound::parameterChanged()
{
    synth.soundParameterChanged();
}
