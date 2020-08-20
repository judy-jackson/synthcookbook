//
//  SynthWaveform.h
//  SynthCookbook
//
//  Created by Jackson, Judith on 8/20/20.
//

#ifndef SynthWaveform_h
#define SynthWaveform_h


#endif /* SynthWaveform_h */

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class SynthWaveform
{
private:
    enum WaveformTypeIndex {
        kSine, kTriangle, kSquare, kSawtooth,
        kNumberOfWaveformTypes
    } index;
    
    friend class SynthCookbookFFTOscillator;
    
public:
    // default constructor
    SynthWaveform() : index(kSine) {}
    
    // set to default state after construction
    void setToDefault() { index = kSine; }
    
    // serialize: get human-readable name of this waveform
    juce::String name();
    
    // deserialize: set index based on given name
    void setFromName(juce::String wfName);
    
    // convenience funtions to allow selecting SynthWaveform from a juce::comboBox
    static void setupComboBox(juce::ComboBox& cb);
    void fromComboBox(juce::ComboBox& cb);
    void toComboBox(juce::ComboBox& cb);
    
    
private:
    // waveform names: ordered list of string literals
    static const char* const wfNames[];
};
