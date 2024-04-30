/*
  ==============================================================================

    DelayComponent.cpp
    Created: 29 Apr 2024 9:02:31pm
    Author:  ant3b

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DelayComponent.h"

//==============================================================================
DelayComponent::DelayComponent(juce::AudioProcessorValueTreeState& apvts)
{

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    delayTimeAttachment = std::make_unique<SliderAttachment>(apvts, "DELAY_TIME", delayTimeSlider);
    delayFeedbackAttachment = std::make_unique<SliderAttachment>(apvts, "DELAY_FEEDBACK", delayFeedbackSlider);
    delayMixAttachment = std::make_unique<SliderAttachment>(apvts, "DELAY_MIX", delayMixSlider);

    setSliderParams(delayTimeSlider);
    setSliderParams(delayFeedbackSlider);
    setSliderParams(delayMixSlider);

    delayTimeLabel.setText("Time", juce::dontSendNotification);
    delayFeedbackLabel.setText("Feedback", juce::dontSendNotification);
    delayMixLabel.setText("Mix", juce::dontSendNotification);

    delayTimeLabel.setJustificationType(juce::Justification::centred);
    delayFeedbackLabel.setJustificationType(juce::Justification::centred);
    delayMixLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(delayTimeLabel);
    addAndMakeVisible(delayFeedbackLabel);
    addAndMakeVisible(delayMixLabel);

}

DelayComponent::~DelayComponent()
{
}

void DelayComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.setColour(juce::Colours::black);
    g.fillRoundedRectangle(0, 0, getWidth(), getHeight(), 10.f);

    g.setColour(juce::Colours::white);
    g.drawText("Delay", 0, 0, getWidth(), 20, juce::Justification::centred, false);
}

void DelayComponent::resized()
{

    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 25;
    const auto sliderWidth = 80;
    const auto sliderHeight = 80;
    const auto sliderStartX = 20;
    const auto sliderStartY = 40;

    delayTimeSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    delayFeedbackSlider.setBounds(delayTimeSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    delayMixSlider.setBounds(75, sliderStartY + 100, sliderWidth, sliderHeight);

    delayTimeLabel.setBounds(sliderStartX, sliderStartY - 20, sliderWidth, 20);
    delayFeedbackLabel.setBounds(delayTimeSlider.getRight() + padding, sliderStartY - 20, sliderWidth, 20);
    delayMixLabel.setBounds(75, sliderStartY + 80, sliderWidth, 20);

}

void DelayComponent::setSliderParams(juce::Slider& slider) {

    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    slider.setColour(juce::Slider::thumbColourId, juce::Colours::white);
    slider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::darkgrey);
    slider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::grey);
    addAndMakeVisible(slider);

}