/*
  ==============================================================================

    DelayComponent.h
    Created: 29 Apr 2024 9:02:31pm
    Author:  ant3b

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class DelayComponent  : public juce::Component
{
public:
    DelayComponent(juce::AudioProcessorValueTreeState& apvts);
    ~DelayComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    void setSliderParams(juce::Slider& slider);

    juce::Slider delayTimeSlider;
    juce::Slider delayFeedbackSlider;
    juce::Slider delayMixSlider;

    juce::Label delayTimeLabel;
    juce::Label delayFeedbackLabel;
    juce::Label delayMixLabel;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<SliderAttachment> delayTimeAttachment;
    std::unique_ptr<SliderAttachment> delayFeedbackAttachment;
    std::unique_ptr<SliderAttachment> delayMixAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayComponent)
};
