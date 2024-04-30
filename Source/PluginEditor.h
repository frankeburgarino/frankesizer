/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/ADSRComponent.h"
#include "UI/OscComponent.h"
#include "UI/ChorusComponent.h"
#include "UI/DelayComponent.h"

//==============================================================================
/**
*/
class FrankesizerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    FrankesizerAudioProcessorEditor (FrankesizerAudioProcessor&);
    ~FrankesizerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    FrankesizerAudioProcessor& audioProcessor;

    OscComponent osc;

    ADSRComponent adsr;

    ChorusComponent chorus;

    DelayComponent delay;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FrankesizerAudioProcessorEditor)

};
