/*
  ==============================================================================

    SynthVoice.cpp
    Created: 28 Aug 2020 2:35:59pm
    Author:  Jackson, Judith

  ==============================================================================
*/


#include "SynthVoice.h"
#include "SynthSound.h"

void SynthVoice::initializeOscTables()
{
    osc1.initializeWavetable();
    osc2.initializeWavetable();
}

bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<SynthSound*> (sound) != nullptr;
}

void SynthVoice::startNote (int midiNoteNumber, float velocity,
                juce::SynthesiserSound* /*sound*/,
                int /*currentPitchWheelPosition*/)
{
    //juce::Logger::getCurrentLogger()->writeToLog("Start note\n");
    osc1.resetCurrentAngle();
    osc2.resetCurrentAngle();
    
    level = velocity * 0.15;
    tailOff = 0.0;
    
    double frequency = juce::MidiMessage::getMidiNoteInHertz (midiNoteNumber);
    //double ff = frequency;
    auto cyclesPerSample = frequency / sampleRate;
    osc1.setFrequency(cyclesPerSample, frequency);
    osc2.setFrequency(cyclesPerSample, frequency);
    
    //pass env params to env generator
    ampEG.attackSeconds = attackSeconds;
    ampEG.decaySeconds = decaySeconds;
    ampEG.sustainLevel = sustainLevel;
    ampEG.releaseSeconds = releaseSeconds;
    
    ampEG.start(sampleRate);
    
    isNoteOff = false;
}

void SynthVoice::stopNote (float /*velocity*/, bool allowTailOff)
{
    ampEG.release();
}

void SynthVoice::renderNextBlock (juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
        while (--numSamples >= 0)
        {
            if (!ampEG.isRunning()){

                clearCurrentNote();
                break;
                
            }
            
            float egLevel = ampEG.getSample();
            auto currentSample = (osc1.getSample() * osc1.getLevel() + osc2.getSample() * osc2.getLevel()) * egLevel;
            
            for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                outputBuffer.addSample (i, startSample, currentSample);
            
            ++startSample;

    }
}


