/*
  ==============================================================================

    ChorusData.h
    Created: 29 Apr 2024 8:56:50pm
    Author:  ant3b

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ChorusData : public juce::dsp::Chorus<float> {

public:

    void updateChorus(const float depth, const float rate, const float feedback, const float mix);

private:

    

};