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

wavetable* SynthWavetable::getTable(SynthWaveform waveform, float freq) //freq as Hz
{
    wavetable *outTable;
    ofstream tableFile;
    tableFile.open("wavetable.csv");
    int tableIndex = getTableIndex(freq);
    juce::String out;
    out << "Current table index " << tableIndex << " for frequency " << freq << "\n";
    juce::Logger::getCurrentLogger()->writeToLog(out);
    switch (waveform.index)
    {
        case SynthWaveform::kSine:
            //get sine table
            juce::Logger::getCurrentLogger()->writeToLog("Sine waveform");
            outTable = &(sawTables[tableIndex]); //replace w/ eventual sine table
            break;
            
        case SynthWaveform::kSquare:
            juce::Logger::getCurrentLogger()->writeToLog("Square waveform");
            outTable = &(squareTables[tableIndex]); //replace hard coded value w/ index
            break;
            
        case SynthWaveform::kSawtooth:
            juce::Logger::getCurrentLogger()->writeToLog("Sawtooth waveform");
            //outTable = sawTables[tableIndex]; //for some reason, returning -1/1 on 
            outTable = &(sawTables[tableIndex]);
            break;
            
        case SynthWaveform::kTriangle:
            juce::Logger::getCurrentLogger()->writeToLog("Triangle waveform");
            outTable = &(triTables[tableIndex]);
            break;
    }
    printTable(outTable, tableFile);
    return outTable;
}

int SynthWavetable::getTableIndex(float freq)
{
    int i = 0;
    while (freq>tableFrequencies[i]) {
        i++;
    }
    return i;
}

void SynthWavetable::initializeTables()
{
    generateTables(sawTables, numTables, initTableSize, initTopFreq, sawtoothWave, "sawtooth.csv");
    generateTables(squareTables, numTables, initTableSize, initTopFreq, squareWave, "square.csv");
    generateTables(triTables, numTables, initTableSize, initTopFreq, triangleWave, "triangle.csv");
    //do something for sine
}

void SynthWavetable::generateTables(wavetable* tables, int numTables, int initSize, float initFreq, float waveformFunc(float), string filename)
{
    int size = initSize;
    float topFreq = initFreq;
    ofstream tablePlot;
    tablePlot.open(filename);
    
    int i;
    for(i=0; i<numTables; i++){
        wavetable table = newTable(size, topFreq);
        double tableDelta = TWO_PI / (double) (size - 1);
        std::cout << filename << "\n";
        fillArray(table.table, table.end, tableDelta, waveformFunc, size);
        printTable(&table, tablePlot);
        if(size > minimumTableSize) size /=2; 
        topFreq*=2;
        *tables = table;
        tables++;
        tablePlot << "\n";
    }
    tablePlot.close();
}

wavetable SynthWavetable::newTable(int size, float topFreq)
{
    printf("Generating table of size %d with top frequency at %f and bottom frequency at %f\n", size, topFreq, topFreq/2.0);
    wavetable initTable;
    initTable.size = size;
    initTable.table = new float[size];
    initTable.highestFreq = topFreq;
    initTable.lowestFreq = topFreq/2.0;
    initTable.end = initTable.table + (size - 1);
    std::cout << "New array has table start: " << initTable.table << ", table end: " << initTable.end << "\n";
    return initTable;
}

void SynthWavetable::fillArray(float* table, float* end, double increment, float waveformFunc(float), int size)
{
    
    float* ptr = table;
    size -=1; //for wrapping purposes
    double delta = 0;
    int index = 0;
    //std::cout << "Filling array, table start: " << &table << ", table end: " << &end << "\n";
    //printf("Table start: %f, table end: %f\n", &table, &end);
    while(table != end){
    //while(ptr != end){
        delta = (double) index / size;
        //*ptr = waveformFunc(delta);
        *table = waveformFunc(delta);
        //printf("Index: %d, value: %f\n", index, *ptr);
        printf("Index: %d, value: %f\n", index, *table);
        //ptr++;
        table++;
        index++;
    }
    //*ptr = *table; //wrap the wavetable
    *table = *ptr;
}


void SynthWavetable::printTable(wavetable* table, ofstream& outfile)
{
    juce::Logger::getCurrentLogger()->writeToLog("Writing table to file...\n");
    float* ptr = table->table;
    int index = 0;
    while (ptr != (table->end + 1)) {
        outfile << index;
        outfile << ",";
        outfile << *ptr;
        outfile << "\n";
        index++;
        ptr++;
    }
}
