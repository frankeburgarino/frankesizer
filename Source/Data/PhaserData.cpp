/*
  ==============================================================================

    DelayData.cpp
    Created: 29 Apr 2024 9:03:12pm
    Author:  ant3b

  ==============================================================================
*/

#include "PhaserData.h"

void PhaserData::updatePhaser(const float depth, const float rate, const float feedback, const float mix) {
    setDepth(depth);
    setRate(rate);
    setFeedback(feedback);
    setMix(mix);
}