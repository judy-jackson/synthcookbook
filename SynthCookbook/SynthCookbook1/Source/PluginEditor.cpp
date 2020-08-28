/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthCookbookAudioProcessorEditor::SynthCookbookAudioProcessorEditor (SynthCookbookAudioProcessor& p)
    : AudioProcessorEditor (&p), keyboardComponent (p.keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    addAndMakeVisible (keyboardComponent);
    setSize (400, 300);
    
    startTimer (400);
    juce::String message;
    message << "Keyboard component added and initialized. \n";
    juce::Logger::getCurrentLogger()->writeToLog(message);
}

SynthCookbookAudioProcessorEditor::~SynthCookbookAudioProcessorEditor()
{
}

//==============================================================================
void SynthCookbookAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void SynthCookbookAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    keyboardComponent.setBounds (10, 10, getWidth() - 20, getHeight() - 20);
}

void SynthCookbookAudioProcessorEditor:: timerCallback()
{
    keyboardComponent.grabKeyboardFocus();
    juce::Timer::stopTimer();
    juce::String message;
    message << "Callback function complete \n";
    juce::Logger::getCurrentLogger()->writeToLog(message);
}
