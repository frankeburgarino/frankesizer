/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FrankesizerAudioProcessorEditor::FrankesizerAudioProcessorEditor (FrankesizerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), osc(audioProcessor.apvts, "OSC"), adsr(audioProcessor.apvts), chorus(audioProcessor.apvts), phaser(audioProcessor.apvts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 400);

    addAndMakeVisible(adsr);
    addAndMakeVisible(osc);
    addAndMakeVisible(chorus);
    addAndMakeVisible(phaser);

}

FrankesizerAudioProcessorEditor::~FrankesizerAudioProcessorEditor()
{
}

//==============================================================================
void FrankesizerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::darkgrey);

    g.setColour (juce::Colours::black);

    g.fillRoundedRectangle(10, getHeight() - 110, 480, 100, 10.f);
    
    g.fillRoundedRectangle(260, getHeight() - 350, 230, 230, 10.f);

    g.fillRoundedRectangle(150, 10, 200, 30, 10.f);

    g.setColour(juce::Colours::white);

    g.setFont(30);

    g.drawText("FRANKESIZER", 0, 10, getWidth(), 30, juce::Justification::centred, false);
}

void FrankesizerAudioProcessorEditor::resized()
{

    osc.setBounds(10, getHeight() - 70, 100, 30);
    adsr.setBounds(100, getHeight() - 110, 400, 100);
    chorus.setBounds(10, getHeight() - 350, 230, 230);
    phaser.setBounds(260, getHeight() - 350, 230, 230);

}