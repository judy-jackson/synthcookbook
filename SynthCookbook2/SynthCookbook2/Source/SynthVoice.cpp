/*
  ==============================================================================

    SynthVoice.cpp
    Created: 28 Aug 2020 2:35:59pm
    Author:  Jackson, Judith

  ==============================================================================
*/


#include "SynthVoice.h"
#include "SynthSound.h"

bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<SynthSound*> (sound) != nullptr;
}

void SynthVoice::startNote (int midiNoteNumber, float velocity,
                juce::SynthesiserSound* /*sound*/,
                int /*currentPitchWheelPosition*/)
{
    osc1.resetCurrentAngle();
    osc2.resetCurrentAngle();
    level = velocity * 0.15;
    tailOff = 0.0;
    
    auto cyclesPerSecond = juce::MidiMessage::getMidiNoteInHertz (midiNoteNumber);
    auto cyclesPerSample = cyclesPerSecond / sampleRate; //move this to oscillator class
    
    osc1.setFrequency(cyclesPerSample);
    osc2.setFrequency(cyclesPerSample);
    isNoteOff = false;
}

void SynthVoice::stopNote (float /*velocity*/, bool allowTailOff)
{
    if (allowTailOff)
    {
        // start a tail-off by setting this flag. The render callback will pick up on
        // this and do a fade out, calling clearCurrentNote() when it's finished.
        
        if (tailOff == 0.0) // we only need to begin a tail-off if it's not already doing so - the
            // stopNote method could be called more than once.
            tailOff = 1.0;
    }
    else
    {
        // we're being told to stop playing immediately, so reset everything..
        clearCurrentNote();
        isNoteOff = true;
    }
}

void SynthVoice::renderNextBlock (juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
        while (--numSamples >= 0 && !isNoteOff)
        {
            auto currentSample = (osc1.getSample() * osc1.getLevel() + osc2.getSample() * osc2.getLevel()) * level;
            
            for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                outputBuffer.addSample (i, startSample, currentSample);
            
            ++startSample;
            
            if (tailOff > 0.0)
            {
                tailOff *= 0.99;
                if (tailOff <= 0.005)
                {
                    // tells the synth that this voice has stopped
                    clearCurrentNote();
                    isNoteOff = true;

                }
            }
    }
}


