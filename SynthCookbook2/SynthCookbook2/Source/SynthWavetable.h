/*
  ==============================================================================

    SynthWavetable.h
    Created: 6 Oct 2020 1:47:51pm
    Author:  Jackson, Judith

  ==============================================================================
*/

#pragma once
#include "SynthWaveform.h"
#include <iostream>
#include <fstream>
using namespace std;

//wavetable struct
typedef struct {
    int size;
    float highestFreq;
    float* end;
    float* table;
    
} wavetable;

class SynthWavetable {
    
    private:
        constexpr static const float initTopFreq = 32.703; // corresponds to MIDI note C1
        static const int minimumTableSize = 128; // no reasoning for this being the cutoff other than JUCE tutorial using this for their default size
        constexpr static const double TWO_PI = juce::MathConstants<double>::twoPi;
        static const int initTableSize = 1 << 10;
    
        static wavetable newTable(int size, float topFreq);
        static void fillArray(float* table, float* end, double increment, float waveformFunc(float), int size);
        static void generateTables(wavetable* tables, int numTables, int initSize, float initFreq, float waveformFunc(float));
    
        static float sawtoothWave(float phi){ return 2.0f * phi - 1.0f;; }
        static float triangleWave(float phi){ return (2.0f * (0.5f - std::fabs(phi - 0.5f)) - 1.0f); }
        static float squareWave(float phi){ return (phi <= 0.5f) ? 1.0f : -1.0f;; }
    
        static ofstream logfile;
    
    public:
        //what to do about constructor? doing dummy constructor for now, could eventually put init func in constructor?
        SynthWavetable() {};
    
        static void initializeTables(); //static initialization method so
        //float getSample(SynthWaveform waveform, int index, float tableDelta);
        static void printTable(wavetable table);
        wavetable getTable(SynthWaveform waveform, float freq);
    
        static const int numTables = 8;    
        static wavetable sawTables[numTables];
        static wavetable squareTables[numTables];
        static wavetable triTables[numTables];
        static float sineTable[initTableSize];
    
};
