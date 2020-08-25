//
//  SynthOscillator.h
//  SynthCookbook
//
//  Created by Jackson, Judith on 8/25/20.
//

#ifndef SynthOscillator_h
#define SynthOscillator_h


#endif /* SynthOscillator_h */

#pragma once
#include "SynthParameters.h"

class SynthOscillator
{
private:
    //SynthWaveform waveform;
    double phase;            // [0.0, 1.0]
    double phaseDelta;        // cycles per sample (fraction)
    
public:
    SynthOscillator() : phase(0), phaseDelta(0) {}
    
    //void setWaveform(SynthWaveform wf) { waveform = wf; }
    void setFrequency(double cyclesPerSample) { phaseDelta = cyclesPerSample; }
    
    float getSample ();
};
