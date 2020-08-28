/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SynthVoice.h"

//==============================================================================
SynthCookbookAudioProcessor::SynthCookbookAudioProcessor(juce::MidiKeyboardState& keyState)
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    initializePrograms();
    
    juce::String message;
    message << "Programs initialized in AudioProcessor \n";
    juce::Logger::getCurrentLogger()->writeToLog(message);
    
    for (int i = 0; i < kNumberOfVoices; ++i)
        synth.addVoice(new SynthVoice());
    
    juce::Logger::getCurrentLogger()->writeToLog("Synth voices added \n");
    
    pSound = new SynthSound(synth);
    pSound->pParams = &programBank[currentProgram];
    synth.addSound(pSound);
    
    juce::Logger::getCurrentLogger()->writeToLog("Sound added to synth \n");
    
}

SynthCookbookAudioProcessor::SynthCookbookAudioProcessor()
{
    
    new SynthCookbookAudioProcessor(keyboardState);
    juce::Logger::getCurrentLogger()->writeToLog("Zero argument constructor \n");
}


void SynthCookbookAudioProcessor::initializePrograms()
{
    for (int i = 0; i < kNumberOfPrograms; i++)
        programBank[i].setDefaultValues();
}

//==============================================================================
const juce::String SynthCookbookAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SynthCookbookAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SynthCookbookAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SynthCookbookAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SynthCookbookAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthCookbookAudioProcessor::getNumPrograms()
{
    return kNumberOfPrograms;
}

int SynthCookbookAudioProcessor::getCurrentProgram()
{
    return 1;
}

void SynthCookbookAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SynthCookbookAudioProcessor::getProgramName (int index)
{
    return {};
}

void SynthCookbookAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SynthCookbookAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::Logger::getCurrentLogger()->writeToLog("Preparing to play... \n");
    keyboardState.reset();
    synth.setCurrentPlaybackSampleRate(sampleRate);
    juce::Logger::getCurrentLogger()->writeToLog("Play setup finished \n");
    
}

void SynthCookbookAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    keyboardState.reset();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthCookbookAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SynthCookbookAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    auto numSamples = buffer.getNumSamples();
    
    //juce::Logger::getCurrentLogger()->writeToLog("Processing block of audio \n");
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, numSamples);

    // Now pass any incoming midi messages to our keyboard state object, and let it
    // add messages to the buffer if the user is clicking on the on-screen keys 
    keyboardState.processNextMidiBuffer (midiMessages, 0, numSamples, true);
    
    synth.renderNextBlock (buffer, midiMessages, 0, numSamples);
}

//==============================================================================
bool SynthCookbookAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SynthCookbookAudioProcessor::createEditor()
{
    return new SynthCookbookAudioProcessorEditor (*this);
}

//==============================================================================
void SynthCookbookAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SynthCookbookAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthCookbookAudioProcessor();
}
