/*
  ==============================================================================

    Main.cpp
    Created: 28 Aug 2020 2:35:31pm
    Author:  Jackson, Judith

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthCookbook2AudioProcessor();
}
