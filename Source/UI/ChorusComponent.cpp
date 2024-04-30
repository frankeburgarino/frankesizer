/*
  ==============================================================================

    ChorusComponent.cpp
    Created: 29 Apr 2024 8:56:30pm
    Author:  ant3b

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ChorusComponent.h"

//==============================================================================
ChorusComponent::ChorusComponent(juce::AudioProcessorValueTreeState& apvts)
{

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    chorusDepthAttachment = std::make_unique<SliderAttachment>(apvts, "CHORUS_DEPTH", chorusDepthSlider);
    chorusRateAttachment = std::make_unique<SliderAttachment>(apvts, "CHORUS_RATE", chorusRateSlider);
    chorusFeedbackAttachment = std::make_unique<SliderAttachment>(apvts, "CHORUS_FEEDBACK", chorusFeedbackSlider);
    chorusMixAttachment = std::make_unique<SliderAttachment>(apvts, "CHORUS_MIX", chorusMixSlider);

    setSliderParams(chorusDepthSlider);
    setSliderParams(chorusRateSlider);
    setSliderParams(chorusFeedbackSlider);
    setSliderParams(chorusMixSlider);

    chorusDepthLabel.setText("Depth", juce::dontSendNotification);
    chorusRateLabel.setText("Rate", juce::dontSendNotification);
    chorusFeedbackLabel.setText("Feedback", juce::dontSendNotification);
    chorusMixLabel.setText("Mix", juce::dontSendNotification);

    chorusDepthLabel.setJustificationType(juce::Justification::centred);
    chorusRateLabel.setJustificationType(juce::Justification::centred);
    chorusFeedbackLabel.setJustificationType(juce::Justification::centred);
    chorusMixLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(chorusDepthLabel);
    addAndMakeVisible(chorusRateLabel);
    addAndMakeVisible(chorusFeedbackLabel);
    addAndMakeVisible(chorusMixLabel);

}

ChorusComponent::~ChorusComponent()
{
}

void ChorusComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    g.setColour(juce::Colours::black);
    g.fillRoundedRectangle(0, 0, getWidth(), getHeight(), 10.f);
    
    g.setColour(juce::Colours::white);
    g.drawText("Chorus", 0, 0, getWidth(), 20, juce::Justification::centred, false);
}

void ChorusComponent::resized()
{

    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 25;
    const auto sliderWidth = 80;
    const auto sliderHeight = 80;
    const auto sliderStartX = 20;
    const auto sliderStartY = 40;

    chorusDepthSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    chorusRateSlider.setBounds(chorusDepthSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    chorusFeedbackSlider.setBounds(sliderStartX, sliderStartY + 100, sliderWidth, sliderHeight);
    chorusMixSlider.setBounds(chorusFeedbackSlider.getRight() + padding, sliderStartY + 100, sliderWidth, sliderHeight);

    chorusDepthLabel.setBounds(sliderStartX, sliderStartY - 20, sliderWidth, 20);
    chorusRateLabel.setBounds(chorusDepthSlider.getRight() + padding, sliderStartY - 20, sliderWidth, 20);
    chorusFeedbackLabel.setBounds(sliderStartX, sliderStartY + 80, sliderWidth, 20);
    chorusMixLabel.setBounds(chorusFeedbackSlider.getRight() + padding, sliderStartY + 80, sliderWidth, 20);

}

void ChorusComponent::setSliderParams(juce::Slider& slider) {

    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    slider.setColour(juce::Slider::thumbColourId, juce::Colours::white);
    slider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::darkgrey);
    slider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::grey);
    addAndMakeVisible(slider);

}