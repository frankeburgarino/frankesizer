/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FrankesizerAudioProcessorEditor::FrankesizerAudioProcessorEditor (FrankesizerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), osc(audioProcessor.apvts, "OSC"), adsr(audioProcessor.apvts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    addAndMakeVisible(adsr);
    addAndMakeVisible(osc);

}

FrankesizerAudioProcessorEditor::~FrankesizerAudioProcessorEditor()
{
}

//==============================================================================
void FrankesizerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
}

void FrankesizerAudioProcessorEditor::resized()
{
 
    osc.setBounds(10, 10, 100, 30);
    adsr.setBounds(getLocalBounds());

}