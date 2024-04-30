/*
  ==============================================================================

    OscComponent.cpp
    Created: 29 Apr 2024 6:02:24pm
    Author:  ant3b

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId)
{

    juce::StringArray choices{ "Sine", "Saw", "Square" };
    oscWaveSelector.addItemList(choices, 1);
    oscWaveSelector.setColour(juce::ComboBox::backgroundColourId, juce::Colours::darkgrey);
    addAndMakeVisible(oscWaveSelector);

    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveSelectorId, oscWaveSelector);

}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    //g.fillAll(juce::Colours::black);
}

void OscComponent::resized()
{
    oscWaveSelector.setBounds(10, 0, 80, 20);
}
