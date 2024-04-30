/*
  ==============================================================================

    ChorusData.cpp
    Created: 29 Apr 2024 8:56:50pm
    Author:  ant3b

  ==============================================================================
*/

#include "ChorusData.h"

void ChorusData::updateChorus(const float depth, const float rate, const float feedback, const float mix) {
    setDepth(depth);
    setRate(rate);
    setFeedback(feedback);
    setMix(mix);
}