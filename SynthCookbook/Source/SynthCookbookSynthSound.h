//
//  SynthCookbookSynthSound.h
//  SynthCookbook
//
//  Created by Jackson, Judith on 8/20/20.
//

#ifndef SynthCookbookSynthSound_h
#define SynthCookbookSynthSound_h


#endif /* SynthCookbookSynthSound_h */
#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthParameters.h"

class Synth;

class SynthCookbookSynthSound : public juce::SynthesiserSound
{
private:
    Synth& synth;
    
public:
    SynthCookbookSynthSound(Synth& ownerSynth);
    
    // our sound applies to all notes, all channels
    bool appliesToNote(int /*midiNoteNumber*/) override { return true; }
    bool appliesToChannel(int /*midiChannel*/) override { return true; }
    
    // pointer to currently-used parameters bundle
    SynthParameters* pParams;
    
    // call to notify owner Synth, that parameters have changed
    void parameterChanged();
};
