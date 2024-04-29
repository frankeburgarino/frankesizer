/*
  ==============================================================================

    ADSRData.h
    Created: 29 Apr 2024 3:51:14pm
    Author:  ant3b

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ADSRData : public juce::ADSR {

public:

    void updateADSR(const float attack, const float decay, const float sustain, const float release);

private:

    juce::ADSR::Parameters adsrParams;

};