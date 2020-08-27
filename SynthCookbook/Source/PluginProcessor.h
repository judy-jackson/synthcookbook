/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthParameters.h"
#include "SynthSound.h"
#include "Synth.h"

//==============================================================================
/**
*/
class SynthCookbookAudioProcessor  : public juce::AudioProcessor
{
//default template-generated code
public:
    //==============================================================================
    SynthCookbookAudioProcessor(juce::MidiKeyboardState& keyState);
    SynthCookbookAudioProcessor();
    ~SynthCookbookAudioProcessor() override = default;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

//custom code to add synthesizer components
public:
    SynthSound* getSound() { return pSound; }
    juce::MidiKeyboardState keyboardState;
    
private:
    static const int kNumberOfPrograms = 128;
    static const int kNumberOfVoices = 16;
    
    Synth synth;
    SynthSound* pSound;
    
    
    juce::MidiMessageCollector midiCollector;
    
    SynthParameters programBank[kNumberOfPrograms];
    int currentProgram;

private:
    //==============================================================================
    void initializePrograms();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthCookbookAudioProcessor)
};
