/*
  ==============================================================================

    OscData.cpp
    Created: 29 Apr 2024 5:46:04pm
    Author:  ant3b

  ==============================================================================
*/

#include "OscData.h"
#define _USE_MATH_DEFINES
#include <math.h>

void OscData::prepareToPlay(juce::dsp::ProcessSpec& spec) {
    prepare(spec);
}

void OscData::setWaveType(const int choice) {

    switch (choice) {
    case 0:
        initialise([](float x) { return std::sin(x); }); // Sine
        break;
    case 1:
        initialise([](float x) { return x / juce::MathConstants<float>::pi; }); // Saw
        break;
    case 2:
        initialise([](float x) { return x < 0.f ? -1.f : 1.f; }); // Square
        break;
    default:
        jassertfalse;
        break;
    }

}

void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& block) {
    process(juce::dsp::ProcessContextReplacing<float>(block));
}

void OscData::setWaveFrequency(const int midiNoteNumber) {
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
}