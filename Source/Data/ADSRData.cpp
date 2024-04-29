/*
  ==============================================================================

    ADSRData.cpp
    Created: 29 Apr 2024 3:51:14pm
    Author:  ant3b

  ==============================================================================
*/

#include "ADSRData.h"

void ADSRData::updateADSR(const float attack, const float decay, const float sustain, const float release) {

    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;

    setParameters(adsrParams);

}