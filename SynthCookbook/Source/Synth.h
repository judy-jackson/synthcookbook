//
//  Synth.h
//  SynthCookbook
//
//  Created by Jackson, Judith on 8/21/20.
//

#ifndef Synth_h
#define Synth_h


#endif /* Synth_h */
#pragma once
/*
 Class Synth represents the Synthesizer itself. It derives from juce::Synthesiser,
 and adds a member function to notify all active voices when any sound parameter
 changes, e.g. when a change has been made in the GUI editor, or due to parameter
 automation from the plugin host (DAW).
 */
#include <JuceHeader.h>
#include "SynthParameters.h"

class Synth : public juce::Synthesiser
{

public:
    //void soundParameterChanged();
};
