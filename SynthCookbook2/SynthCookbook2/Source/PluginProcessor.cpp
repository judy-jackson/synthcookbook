/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SynthVoice.h"
#include "SynthSound.h"
#include "SynthWavetableOscillator.h"

//==============================================================================
SynthCookbook2AudioProcessor::SynthCookbook2AudioProcessor()
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
    SynthWavetable::initializeTables();
    //SynthWavetableOscillator::initializeWavetable(); //change to SynthWavetable::initialize()
    //assign 
    initializeSynth();
}

//SynthCookbook2AudioProcessor::~SynthCookbook2AudioProcessor() {}

//==============================================================================
// CUSTOM FUNCTIONS
//==============================================================================
void SynthCookbook2AudioProcessor::initializeSynth()
{
    auto numVoices = 8;
    
    // Add some voices...
    for (auto i = 0; i < numVoices; ++i)
        
        synth.addVoice (new SynthVoice());
    
    // ..and give the synth a sound to play
    synth.addSound (new SynthSound());
}

template <typename FloatType>
void SynthCookbook2AudioProcessor::process (juce::AudioBuffer<FloatType>& buffer, juce::MidiBuffer& midiMessages)
{
    auto numSamples = buffer.getNumSamples();
    
    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (auto i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
        buffer.clear (i, 0, numSamples);
    
    // Now pass any incoming midi messages to our keyboard state object, and let it
    // add messages to the buffer if the user is clicking on the on-screen keys
    keyboardState.processNextMidiBuffer (midiMessages, 0, numSamples, true);
    
    // and now get our synth to process these midi events and generate its output.
    synth.renderNextBlock (buffer, midiMessages, 0, numSamples);
    
}

//==============================================================================

bool SynthCookbook2AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SynthCookbook2AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

//==============================================================================
void SynthCookbook2AudioProcessor::prepareToPlay (double newSampleRate, int /*samplesPerBlock*/)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    synth.setCurrentPlaybackSampleRate (newSampleRate);
    keyboardState.reset();

}

void SynthCookbook2AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    keyboardState.reset();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthCookbook2AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    // Only mono/stereo and input/output must have same layout
    const auto& mainOutput = layouts.getMainOutputChannelSet();
    const auto& mainInput  = layouts.getMainInputChannelSet();
    
    // input and output layout must either be the same or the input must be disabled altogether
    if (! mainInput.isDisabled() && mainInput != mainOutput)
        return false;
    
    // do not allow disabling the main buses
    if (mainOutput.isDisabled())
        return false;
    
    // only allow stereo and mono
    if (mainOutput.size() > 2)
        return false;
    
    return true;
}
#endif

void SynthCookbook2AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    process(buffer, midiMessages);
}

//==============================================================================

juce::AudioProcessorEditor* SynthCookbook2AudioProcessor::createEditor()
{
    return new SynthCookbook2AudioProcessorEditor (*this);
}

//==============================================================================
void SynthCookbook2AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SynthCookbook2AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

/*
 MOVED TO MAIN.CPP
//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthCookbook2AudioProcessor();
}
 */
