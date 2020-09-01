/*
  ==============================================================================

    SynthVoice.h
    Created: 28 Aug 2020 2:35:59pm
    Author:  Jackson, Judith

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthOscillator.h"

class SynthVoice   : public juce::SynthesiserVoice
{
public:
    SynthVoice() {}
    
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    
    void startNote (int midiNoteNumber, float velocity,
                    juce::SynthesiserSound* /*sound*/,
                    int /*currentPitchWheelPosition*/) override;
    
    void stopNote (float /*velocity*/, bool allowTailOff) override;
    
    void pitchWheelMoved (int /*newValue*/) override {}
    
    void controllerMoved (int /*controllerNumber*/, int /*newValue*/) override {}
    
    void renderNextBlock (juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
    
private:
    
    SynthOscillator osc1, osc2;
    
    auto getNextSample(juce::AudioBuffer<float>& outputBuffer, int startSample);
    
    double currentAngle = 0.0;
    double angleDelta   = 0.0;
    double level        = 0.0;
    double tailOff      = 0.0;
    
    bool isNoteOff;
    
    double sampleRate = getSampleRate();
    
};
