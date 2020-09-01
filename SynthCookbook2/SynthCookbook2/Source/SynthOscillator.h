/*
  ==============================================================================

    SynthOscillator.h
    Created: 28 Aug 2020 2:36:12pm
    Author:  Jackson, Judith

  ==============================================================================
*/

#pragma once

class SynthOscillator
{
private:
    //SynthWaveform waveform;
    double currentAngle;            // [0.0, 1.0]
    double angleDelta;        // cycles per sample (fraction)
    
public:
    //constructor initializes currentAngle, angleDelta
    SynthOscillator() : currentAngle(0), angleDelta(0) {}
    
    //void setWaveform(SynthWaveform wf) { waveform = wf; }
    void resetCurrentAngle() { currentAngle = 0; }
    void setFrequency(double cyclesPerSample) { angleDelta = cyclesPerSample; }
    
    float getSample();
    float getLevel() {return 0.8;}
};
