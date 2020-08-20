//
//  SynthCookbookSynthVoice.h
//  SynthCookbook
//
//  Created by Jackson, Judith on 8/20/20.
//

#ifndef SynthCookbookSynthVoice_h
#define SynthCookbookSynthVoice_h


#endif /* SynthCookbookSynthVoice_h */
#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthCookbookSynthSound.h"
#include "SynthCookbookWavetableOscillator.h"
#include "SynthCookbookFFTOscillator.h"

class SynthCookbookSynthVoice : public SynthesiserVoice
{
private:
    // encapsulated objects which generate/modify sound
    //SynthCookbookWaveformOscillator osc1, osc2;
    SynthCookbookFFTOscillator osc1, osc2;
    
    // current sound parameters
    SynthParameters* pParams; //need to make sure is defined somewhere w/ dummy vals
    
    // voice properties remembered from startNote() call
    float noteVelocity;
    
    // dynamic properties of this voice
    float pitchBend;    // converted to range [-1.0, +1.0]
    LinearSmoothedValue<float> osc1Level, osc2Level;
    bool tailOff;
    
public:
    SynthCookbookSynthVoice();
    
    bool canPlaySound(SynthesiserSound* sound) override
    { return dynamic_cast<SynthSound*> (sound) != nullptr; }
    
    void soundParameterChanged();
    
    void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void pitchWheelMoved(int newValue) override;
    void controllerMoved(int controllerNumber, int newValue) override;
    
    void renderNextBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override;
    
private:
    void setPitchBend(int pitchWheelPosition);
    float pitchBendCents();
    void setup(bool pitchBendOnly);
};
