/*
  ==============================================================================

    ChorusComponent.h
    Created: 29 Apr 2024 8:56:30pm
    Author:  ant3b

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ChorusComponent  : public juce::Component
{
public:
    ChorusComponent(juce::AudioProcessorValueTreeState& apvts);
    ~ChorusComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    void setSliderParams(juce::Slider& slider);

    juce::Slider chorusDepthSlider;
    juce::Slider chorusRateSlider;
    juce::Slider chorusFeedbackSlider;
    juce::Slider chorusMixSlider;

    juce::Label chorusDepthLabel;
    juce::Label chorusRateLabel;
    juce::Label chorusFeedbackLabel;
    juce::Label chorusMixLabel;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<SliderAttachment> chorusDepthAttachment;
    std::unique_ptr<SliderAttachment> chorusRateAttachment;
    std::unique_ptr<SliderAttachment> chorusFeedbackAttachment;
    std::unique_ptr<SliderAttachment> chorusMixAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChorusComponent)
};
