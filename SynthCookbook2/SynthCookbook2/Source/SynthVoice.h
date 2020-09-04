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
#include "SynthWavetableOscillator.h"
#include "SynthAmpEnvGenerator.h"

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
    
    SynthWavetableOscillator osc1, osc2;
    SynthAmpEnvGenerator ampEG;
    
    auto getNextSample(juce::AudioBuffer<float>& outputBuffer, int startSample);
    //void setup();
    
    double currentAngle = 0.0;
    double angleDelta   = 0.0;
    double level        = 0.0;
    double tailOff      = 0.0;
    
    double attackSeconds = 0.5;
    double decaySeconds = 1;
    double releaseSeconds = 0.5;
    double sustainLevel = 0.6;
    
    
    bool isNoteOff;
    
    double sampleRate = getSampleRate();
    
};
