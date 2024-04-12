/*
  ==============================================================================

    SynthSound.h
    Created: 10 Apr 2024 3:05:14pm
    Author:  ant3b

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound {
public:

    bool appliesToNote(int midiNoteNumber) override { return true; }
    bool appliesToChannel(int midiChannel) override { return true; }

};