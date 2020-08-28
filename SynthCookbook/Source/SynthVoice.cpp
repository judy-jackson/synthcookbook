/*
  ==============================================================================

    SynthVoice.cpp
    Created: 26 Aug 2020 4:20:16pm
    Author:  Jackson, Judith

  ==============================================================================
*/

#include "SynthVoice.h"
#include <cmath>

void SynthVoice::setPitchBend(int pitchWheelPos)
{
    if (pitchWheelPos > 8192)
    {
        // shifting up
        pitchBend = float(pitchWheelPos - 8192) / (16383 - 8192);
    }
    else
    {
        // shifting down
        pitchBend = float(8192 - pitchWheelPos) / -8192;    // negative number
    }
}

float SynthVoice::pitchBendCents()
{
    if (pitchBend >= 0.0f)
    {
        // shifting up
        return pitchBend * pParams->pitchBendUpSemitones * 100;
    }
    else
    {
        // shifting down
        return pitchBend * pParams->pitchBendDownSemitones * 100;
    }
}

static double noteHz(int midiNoteNumber, double centsOffset)
{
    double hertz = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    hertz *= std::pow(2.0, centsOffset / 1200);
    return hertz;
}

SynthVoice::SynthVoice()
: SynthesiserVoice()
, pParams(0)
, noteVelocity(0.0f)
, pitchBend(0.0f)
, osc1Level(0.0f)
, osc2Level(0.0f)
, tailOff(false)
{
}

// Set up voice according to current sound parameters and pitch bend
void SynthVoice::setup (bool pitchBendOnly)
{
    double sampleRateHz = getSampleRate();
    int midiNote = getCurrentlyPlayingNote();
    
    //logging for troubleshooting
    juce::String message;
    message << "Current sample rate: " << getSampleRate() << "\n";
    message << "Current MIDI note: " << midiNote << "\n";
    juce::Logger::getCurrentLogger()->writeToLog(message);
    
    float masterLevel = float(noteVelocity * pParams->masterLevel);
    double pbCents = pitchBendCents();
    
    double cyclesPerSecond = noteHz(midiNote + pParams->osc1PitchOffsetSemitones, pParams->osc1DetuneOffsetCents + pbCents);
    double cyclesPerSample = cyclesPerSecond / sampleRateHz;
    osc1.setFrequency(cyclesPerSample);
    if (!pitchBendOnly)
    {
        //osc1.setWaveform(pParams->osc1Waveform);
        osc1Level.reset(sampleRateHz, ampEG.isRunning() ? 0.1 : 0.0); //fix this
        osc1Level.setTargetValue(float(pParams->oscBlend * masterLevel));
    }
    
    cyclesPerSecond = noteHz(midiNote + pParams->osc2PitchOffsetSemitones, pParams->osc2DetuneOffsetCents + pbCents);
    cyclesPerSample = cyclesPerSecond / sampleRateHz;
    osc2.setFrequency(cyclesPerSample);
    if (!pitchBendOnly)
    {
        //osc2.setWaveform(pParams->osc2Waveform);
        osc2Level.reset(sampleRateHz, ampEG.isRunning() ? 0.1 : 0.0);
        osc2Level.setTargetValue(float((1.0 - pParams->oscBlend) * masterLevel));
    }
    
    
    if (!pitchBendOnly)
    {
        ampEG.attackSeconds = pParams->ampEgAttackTimeSeconds;
        ampEG.decaySeconds = pParams->ampEgDecayTimeSeconds;
        ampEG.sustainLevel = pParams->ampEgSustainLevel;
        ampEG.releaseSeconds = pParams->ampEgReleaseTimeSeconds;
    }
     
}
/*
void SynthVoice::soundParameterChanged()
{
    if (pParams == 0) return;
    juce::Logger::getCurrentLogger()->writeToLog("Synth Voice: sound parameter changed \n");
    setup(false);
    
}
 */

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    juce::Logger::getCurrentLogger()->writeToLog("Start note triggered (Synth Voice) \n");
    juce::ignoreUnused(midiNoteNumber);    // accessible as SynthesiserVoice::getCurrentlyPlayingNote();
    tailOff = false;
    noteVelocity = velocity;
    
    pParams = dynamic_cast<SynthSound*>(sound)->pParams;
    double sampleRateHz = getSampleRate();
    setPitchBend(currentPitchWheelPosition);
    
    setup(false);
    ampEG.start(sampleRateHz);
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    juce::ignoreUnused(velocity);
    
    if (allowTailOff & !tailOff)
    {
        tailOff = true;
        ampEG.release();
    }
    else
    {
        clearCurrentNote();
    }
}

void SynthVoice::pitchWheelMoved(int newValue)
{
    setPitchBend(newValue);
    setup(true);
}

void SynthVoice::controllerMoved(int controllerNumber, int newValue)
{
    // nothing yet
    juce::ignoreUnused(controllerNumber);
    juce::ignoreUnused(newValue);
}

void SynthVoice::renderNextBlock(juce::AudioSampleBuffer& outputBuffer, int startSample, int numSamples)
{
    while (--numSamples >= 0)
    {
        if (!ampEG.isRunning())
        {
            clearCurrentNote();
            break;
        }
        float aeg = ampEG.getSample();
        float osc = osc1.getSample() * osc1Level.getNextValue() + osc2.getSample() * osc2Level.getNextValue();
        float sample = aeg * osc;
        outputBuffer.addSample(0, startSample, sample);
        outputBuffer.addSample(1, startSample, sample);
        ++startSample;
    }
}
