//
//  SynthSound.h
//  SynthCookbook
//
//  Created by Jackson, Judith on 8/21/20.
//

#ifndef SynthSound_h
#define SynthSound_h


#endif /* SynthSound_h */
#pragma once
#include <JuceHeader.h>
#include "SynthParameters.h"

class Synth;

class SynthSound : public juce::SynthesiserSound
{
private:
    Synth& synth;
    
public:
    SynthSound(Synth& ownerSynth);
    
    // our sound applies to all notes, all channels
    bool appliesToNote(int /*midiNoteNumber*/) override { return true; }
    bool appliesToChannel(int /*midiChannel*/) override { return true; }
    
    // pointer to currently-used parameters bundle
    SynthParameters* pParams;
    
    // call to notify owner Synth, that parameters have changed
    void parameterChanged();
};
