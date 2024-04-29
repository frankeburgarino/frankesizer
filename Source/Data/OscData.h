/*
  ==============================================================================

    OscData.h
    Created: 29 Apr 2024 5:46:04pm
    Author:  ant3b

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class OscData : public juce::dsp::Oscillator<float> {

public:

    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void setWaveType(const int choice);
    void setWaveFrequency(const int midiNoteNumber);
    void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& block);

private:



};