/*
  ==============================================================================

    PhaserComponent.cpp
    Created: 29 Apr 2024 9:02:31pm
    Author:  ant3b

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PhaserComponent.h"

//==============================================================================
PhaserComponent::PhaserComponent(juce::AudioProcessorValueTreeState& apvts)
{

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    PhaserDepthAttachment = std::make_unique<SliderAttachment>(apvts, "PHASER_DEPTH", PhaserDepthSlider);
    PhaserRateAttachment = std::make_unique<SliderAttachment>(apvts, "PHASER_RATE", PhaserRateSlider);
    PhaserFeedbackAttachment = std::make_unique<SliderAttachment>(apvts, "PHASER_FEEDBACK", PhaserFeedbackSlider);
    PhaserMixAttachment = std::make_unique<SliderAttachment>(apvts, "PHASER_MIX", PhaserMixSlider);

    setSliderParams(PhaserDepthSlider);
    setSliderParams(PhaserRateSlider);
    setSliderParams(PhaserFeedbackSlider);
    setSliderParams(PhaserMixSlider);

    PhaserDepthLabel.setText("Depth", juce::dontSendNotification);
    PhaserRateLabel.setText("Rate", juce::dontSendNotification);
    PhaserFeedbackLabel.setText("Feedback", juce::dontSendNotification);
    PhaserMixLabel.setText("Mix", juce::dontSendNotification);

    PhaserDepthLabel.setJustificationType(juce::Justification::centred);
    PhaserRateLabel.setJustificationType(juce::Justification::centred);
    PhaserFeedbackLabel.setJustificationType(juce::Justification::centred);
    PhaserMixLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(PhaserDepthLabel);
    addAndMakeVisible(PhaserRateLabel);
    addAndMakeVisible(PhaserFeedbackLabel);
    addAndMakeVisible(PhaserMixLabel);

}

PhaserComponent::~PhaserComponent()
{
}

void PhaserComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.setColour(juce::Colours::black);
    g.fillRoundedRectangle(0, 0, getWidth(), getHeight(), 10.f);

    g.setColour(juce::Colours::white);
    g.drawText("Phaser", 0, 0, getWidth(), 20, juce::Justification::centred, false);
}

void PhaserComponent::resized()
{

    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 25;
    const auto sliderWidth = 80;
    const auto sliderHeight = 80;
    const auto sliderStartX = 20;
    const auto sliderStartY = 40;

    PhaserDepthSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    PhaserRateSlider.setBounds(PhaserDepthSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    PhaserFeedbackSlider.setBounds(sliderStartX, sliderStartY + 100, sliderWidth, sliderHeight);
    PhaserMixSlider.setBounds(PhaserFeedbackSlider.getRight() + padding, sliderStartY + 100, sliderWidth, sliderHeight);

    PhaserDepthLabel.setBounds(sliderStartX, sliderStartY - 20, sliderWidth, 20);
    PhaserRateLabel.setBounds(PhaserDepthSlider.getRight() + padding, sliderStartY - 20, sliderWidth, 20);
    PhaserFeedbackLabel.setBounds(sliderStartX, sliderStartY + 80, sliderWidth, 20);
    PhaserMixLabel.setBounds(PhaserFeedbackSlider.getRight() + padding, sliderStartY + 80, sliderWidth, 20);

}

void PhaserComponent::setSliderParams(juce::Slider& slider) {

    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    slider.setColour(juce::Slider::thumbColourId, juce::Colours::white);
    slider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::darkgrey);
    slider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::grey);
    addAndMakeVisible(slider);

}