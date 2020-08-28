/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class SynthCookbook2AudioProcessorEditor
: public juce::AudioProcessorEditor
, private juce::Timer
{
public:
    SynthCookbook2AudioProcessorEditor (SynthCookbook2AudioProcessor&);
    ~SynthCookbook2AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void timerCallback() override;
    void hostMIDIControllerIsAvailable (bool controllerIsAvailable) override;
    
    

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SynthCookbook2AudioProcessor& audioProcessor;
    
    juce::MidiKeyboardComponent midiKeyboard;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthCookbook2AudioProcessorEditor)
};
