//
//  SynthVoice.h
//  SynthCookbook
//
//  Created by Jackson, Judith on 8/21/20.
//

#ifndef SynthVoice_h
#define SynthVoice_h


#endif /* SynthVoice_h */
#include "SynthSound.h"
#include "SynthOscillator.h"
#include <JuceHeader.h>
#include "SynthParameters.h"
#include "SynthEnvelopeGenerator.h"
//#include "SynthEnvelopeGenerator.h"

class SynthVoice : public juce::SynthesiserVoice
{
private:
    // encapsulated objects which generate/modify sound
    SynthOscillator osc1, osc2;
    SynthEnvelopeGenerator ampEG;
    
    // current sound parameters
    SynthParameters* pParams;
    
    // voice properties remembered from startNote() call
    float noteVelocity;
    
    // dynamic properties of this voice
    float pitchBend;    // converted to range [-1.0, +1.0]
    juce::LinearSmoothedValue<float> osc1Level, osc2Level;
    bool tailOff;
    
public:
    SynthVoice();
    
    bool canPlaySound(juce::SynthesiserSound* sound) override
    { return dynamic_cast<SynthSound*> (sound) != nullptr; }
    
    void soundParameterChanged();
    
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void pitchWheelMoved(int newValue) override;
    void controllerMoved(int controllerNumber, int newValue) override;
    
    void renderNextBlock(juce::AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override;
    
private:
    void setPitchBend(int pitchWheelPosition);
    float pitchBendCents();
    void setup(bool pitchBendOnly);
};
