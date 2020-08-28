/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthCookbook2AudioProcessorEditor::SynthCookbook2AudioProcessorEditor (SynthCookbook2AudioProcessor& audioprocessor)
    : AudioProcessorEditor (&audioprocessor)
    , audioProcessor (audioprocessor)
    , midiKeyboard         (audioprocessor.keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
{
    // add the midi keyboard component..
    addAndMakeVisible (midiKeyboard);
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    startTimer (400);
    
    // don't think I need these, but keeping for thoroughness' sake
    //updateTrackProperties();
    //startTimerHz (30);
}

SynthCookbook2AudioProcessorEditor::~SynthCookbook2AudioProcessorEditor() {};

//==============================================================================
void SynthCookbook2AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour (juce::Colours::white);
    
    //g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void SynthCookbook2AudioProcessorEditor::resized()
{
    //lay out positions of subcomponents
    auto r = getLocalBounds().reduced (8);
    midiKeyboard.setBounds(r.removeFromBottom (70));
}

void SynthCookbook2AudioProcessorEditor::timerCallback()
{
    midiKeyboard.grabKeyboardFocus();
    juce::Timer::stopTimer();
}

void SynthCookbook2AudioProcessorEditor::hostMIDIControllerIsAvailable (bool controllerIsAvailable)
{
    midiKeyboard.setVisible (! controllerIsAvailable);
}
