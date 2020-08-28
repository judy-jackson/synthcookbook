/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class SynthCookbook2AudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    SynthCookbook2AudioProcessor();
    ~SynthCookbook2AudioProcessor() override = default;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
    
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    //==============================================================================
    const juce::String getName() const override { return "Synthesizer Cookbook"; }

    bool acceptsMidi() const override { return true; }
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override { return 0.0; }

    //==============================================================================
    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram (int index) override {}
    const juce::String getProgramName (int index) override { return {}; }
    void changeProgramName (int index, const juce::String& newName) override {}

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    
    
    //==============================================================================
    // CUSTOM VARIABLES (NOT FROM TEMPLATE)
    //==============================================================================
    //event object for keyboard
    juce::MidiKeyboardState keyboardState;

private:
    
    juce::Synthesiser synth;
    
    template <typename FloatType>
    void process(juce::AudioBuffer<FloatType>& buffer, juce::MidiBuffer& midiMessages);
    void initializeSynth();
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthCookbook2AudioProcessor)
};
