/*
  ==============================================================================

    PhaserComponent.h
    Created: 29 Apr 2024 9:02:31pm
    Author:  ant3b

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class PhaserComponent  : public juce::Component
{
public:
    PhaserComponent(juce::AudioProcessorValueTreeState& apvts);
    ~PhaserComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    void setSliderParams(juce::Slider& slider);

    juce::Slider PhaserDepthSlider;
    juce::Slider PhaserRateSlider;
    juce::Slider PhaserFeedbackSlider;
    juce::Slider PhaserMixSlider;

    juce::Label PhaserDepthLabel;
    juce::Label PhaserRateLabel;
    juce::Label PhaserFeedbackLabel;
    juce::Label PhaserMixLabel;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<SliderAttachment> PhaserDepthAttachment;
    std::unique_ptr<SliderAttachment> PhaserRateAttachment;
    std::unique_ptr<SliderAttachment> PhaserFeedbackAttachment;
    std::unique_ptr<SliderAttachment> PhaserMixAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhaserComponent)
};
