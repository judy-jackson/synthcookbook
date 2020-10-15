/*
  ==============================================================================

    SynthWavetable.cpp
    Created: 6 Oct 2020 1:47:51pm
    Author:  Jackson, Judith

  ==============================================================================
*/

#include "SynthWavetable.h"

wavetable SynthWavetable::sawTables[numTables];
wavetable SynthWavetable::squareTables[numTables];
wavetable SynthWavetable::triTables[numTables];
float SynthWavetable::sineTable[initTableSize];

wavetable SynthWavetable::getTable(SynthWaveform waveform, float freq)
{
    wavetable outTable;
    switch (waveform.index)
    {
        case SynthWaveform::kSine:
            //get sine table
            juce::Logger::getCurrentLogger()->writeToLog("Sine waveform");
            outTable = sawTables[0]; //replace w/ eventual sine table
            break;
            
        case SynthWaveform::kSquare:
            juce::Logger::getCurrentLogger()->writeToLog("Square waveform");
            outTable = squareTables[0];
            break;
            
        case SynthWaveform::kSawtooth:
            juce::Logger::getCurrentLogger()->writeToLog("Sawtooth waveform");
            outTable = sawTables[0];
            break;
            
        case SynthWaveform::kTriangle:
            juce::Logger::getCurrentLogger()->writeToLog("Triangle waveform");
            outTable = triTables[0];
            break;
    }
    return outTable;
}

void SynthWavetable::initializeTables()
{
    generateTables(sawTables, numTables, initTableSize, initTopFreq, sawtoothWave);
    generateTables(squareTables, numTables, initTableSize, initTopFreq, squareWave);
    generateTables(triTables, numTables, initTableSize, initTopFreq, triangleWave);
    //do something for sine
}

void SynthWavetable::generateTables(wavetable* tables, int numTables, int initSize, float initFreq, float waveformFunc(float))
{
    int size = initSize;
    float topFreq = initFreq;
    
    int i;
    for(i=0; i<numTables; i++){
        wavetable table = newTable(size, topFreq);
        double tableDelta = TWO_PI / (double) (size - 1);
        fillArray(table.table, table.end, tableDelta, waveformFunc, size);
        if(size > minimumTableSize) size /=2; 
        topFreq*=2;
        *tables = table;
        tables++;
    }
}

wavetable SynthWavetable::newTable(int size, float topFreq)
{
    printf("Generating table of size %d with top frequency at %f\n", size, topFreq);
    wavetable initTable;
    initTable.size = size;
    initTable.table = new float[size];
    initTable.highestFreq = topFreq;
    initTable.end = initTable.table + (size - 1);
    return initTable;
}

void SynthWavetable::fillArray(float* table, float* end, double increment, float waveformFunc(float), int size)
{
    
    float* ptr = table;
    size -=1; //for wrapping purposes
    double delta = 0;
    int index = 0;
    while(ptr != end){
        delta = (double) index / size;
        //printf("Delta value: %f, index: %d, size: %d\n", delta, index, size);
        *ptr = waveformFunc(delta);
        ptr++;
        index++;
    }
    *ptr = *table; //wrap the wavetable
}


void SynthWavetable::printTable(wavetable table)
{
    ofstream outfile;
    outfile.open("sawtooth.csv");
    float* ptr = table.table;
    int index = 0;
    while (ptr != (table.end + 1)) {
        outfile << index;
        outfile << ",";
        outfile << *ptr;
        outfile << "\n";
        index++;
        ptr++;
    }
    outfile.close();
}
