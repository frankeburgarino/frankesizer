/*
  ==============================================================================

    PluginEditor.cpp
    Created: 29 Apr 2024 3:49:53pm
    Author:  ant3b

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ADSRComponent.h"

//==============================================================================
ADSRComponent::ADSRComponent(juce::AudioProcessorValueTreeState& apvts)
{
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    attackAttachment = std::make_unique<SliderAttachment>(apvts, "ATTACK", attackSlider);
    decayAttachment = std::make_unique<SliderAttachment>(apvts, "DECAY", decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment>(apvts, "SUSTAIN", sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment>(apvts, "RELEASE", releaseSlider);

    setSliderParams(attackSlider);
    setSliderParams(decaySlider);
    setSliderParams(sustainSlider);
    setSliderParams(releaseSlider);

    attackLabel.setText("Attack", juce::dontSendNotification);
    decayLabel.setText("Decay", juce::dontSendNotification);
    sustainLabel.setText("Sustain", juce::dontSendNotification);
    releaseLabel.setText("Release", juce::dontSendNotification);

    attackLabel.setJustificationType(juce::Justification::centred);
    decayLabel.setJustificationType(juce::Justification::centred);
    sustainLabel.setJustificationType(juce::Justification::centred);
    releaseLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(attackLabel);
    addAndMakeVisible(decayLabel);
    addAndMakeVisible(sustainLabel);
    addAndMakeVisible(releaseLabel);
}

ADSRComponent::~ADSRComponent()
{
}

void ADSRComponent::paint (juce::Graphics& g)
{
    //g.fillAll(juce::Colours::black);
}

void ADSRComponent::resized()
{

    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 20;
    const auto sliderWidth = 80;
    const auto sliderHeight = 80;
    const auto sliderStartX = 10;
    const auto sliderStartY = 20;

    attackSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    decaySlider.setBounds(attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    sustainSlider.setBounds(decaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    releaseSlider.setBounds(sustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);

    attackLabel.setBounds(sliderStartX, sliderStartY - 20, sliderWidth, 20);
    decayLabel.setBounds(attackSlider.getRight() + padding, sliderStartY - 20, sliderWidth, 20);
    sustainLabel.setBounds(decaySlider.getRight() + padding, sliderStartY - 20, sliderWidth, 20);
    releaseLabel.setBounds(sustainSlider.getRight() + padding, sliderStartY - 20, sliderWidth, 20);

}

void ADSRComponent::setSliderParams(juce::Slider& slider) {

    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    slider.setColour(juce::Slider::thumbColourId, juce::Colours::white);
    slider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::darkgrey);
    slider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::grey);
    addAndMakeVisible(slider);

}