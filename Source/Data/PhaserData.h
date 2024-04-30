/*
  ==============================================================================

    DelayData.h
    Created: 29 Apr 2024 9:03:12pm
    Author:  ant3b

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class PhaserData : public juce::dsp::Phaser<float> {

public:

    void updatePhaser(const float depth, const float rate, const float feedback, const float mix);

private:



};