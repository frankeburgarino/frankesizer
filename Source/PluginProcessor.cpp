/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FrankesizerAudioProcessor::FrankesizerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts (*this, nullptr, "Parameters", createParameters())
#endif
{
    synth.addSound(new SynthSound());
    synth.addVoice(new SynthVoice());
}

FrankesizerAudioProcessor::~FrankesizerAudioProcessor()
{
}

//==============================================================================
const juce::String FrankesizerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FrankesizerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FrankesizerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FrankesizerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FrankesizerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FrankesizerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FrankesizerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FrankesizerAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String FrankesizerAudioProcessor::getProgramName (int index)
{
    return {};
}

void FrankesizerAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void FrankesizerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    
    synth.setCurrentPlaybackSampleRate(sampleRate);

    for (int i = 0; i < synth.getNumVoices(); ++i) {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i))) {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumInputChannels());
        }
    }

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = getTotalNumOutputChannels();

    chorus.prepare(spec);
    phaser.prepare(spec);

}

void FrankesizerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FrankesizerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void FrankesizerAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    auto numSamples = buffer.getNumSamples();

    for (int i = 0; i < synth.getNumVoices(); ++i) {

        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i))) {

            // Osc Controls
            // ADSR
            // LFO

            auto& oscWaveChoice = *apvts.getRawParameterValue("OSC");

            auto& attack = *apvts.getRawParameterValue("ATTACK");
            auto& decay = *apvts.getRawParameterValue("DECAY");
            auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
            auto& release = *apvts.getRawParameterValue("RELEASE");

            voice->update(attack.load(), decay.load(), sustain.load(), release.load());
            voice->getOscillator().setWaveType(oscWaveChoice);



        }

    }

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

    auto& chorusDepth = *apvts.getRawParameterValue("CHORUS_DEPTH");
    auto& chorusRate = *apvts.getRawParameterValue("CHORUS_RATE");
    auto& chorusFeedback = *apvts.getRawParameterValue("CHORUS_FEEDBACK");
    auto& chorusMix = *apvts.getRawParameterValue("CHORUS_MIX");

    auto& phaserDepth = *apvts.getRawParameterValue("PHASER_DEPTH");
    auto& phaserRate = *apvts.getRawParameterValue("PHASER_RATE");
    auto& phaserFeedback = *apvts.getRawParameterValue("PHASER_FEEDBACK");
    auto& phaserMix = *apvts.getRawParameterValue("PHASER_MIX");

    chorus.updateChorus(chorusDepth, chorusRate, chorusFeedback, chorusMix);
    phaser.updatePhaser(phaserDepth, phaserRate, phaserFeedback, phaserMix);

    juce::dsp::AudioBlock<float> block{ buffer };
    chorus.process(juce::dsp::ProcessContextReplacing<float>(block));
    phaser.process(juce::dsp::ProcessContextReplacing<float>(block));

}

//==============================================================================
bool FrankesizerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FrankesizerAudioProcessor::createEditor()
{
    return new FrankesizerAudioProcessorEditor (*this);
}

//==============================================================================
void FrankesizerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

    auto currentState = apvts.copyState(); // make a duplicate that won't be updated suring write to file

    std::unique_ptr<juce::XmlElement> xml(currentState.createXml());

    copyXmlToBinary(*xml, destData);

}

void FrankesizerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(data, sizeInBytes));

    juce::ValueTree newTree = juce::ValueTree::fromXml(*xml);

    apvts.replaceState(newTree);

}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FrankesizerAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout FrankesizerAudioProcessor::createParameters() {

    // Combobox: switch oscillators
    // Attack - float
    // Decay - float
    // Sustain - float
    // Release - float

    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // OSC Select
    
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC", "Oscillator", juce::StringArray{ "Sine", "Saw", "Square" }, 0));

    // ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange<float> { 0.f, 1.0f, 0.1f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", juce::NormalisableRange<float> { 0.f, 1.0f, 0.1f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", juce::NormalisableRange<float> { 0.f, 1.0f, 0.1f }, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange<float> { 0.f, 3.0f, 0.1f }, 0.1f));

    // Chorus
    params.push_back(std::make_unique<juce::AudioParameterFloat>("CHORUS_DEPTH", "Chorus Depth", juce::NormalisableRange<float> { 0.f, 0.5f, 0.01f }, 0.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("CHORUS_RATE", "Chorus Rate", juce::NormalisableRange<float> { 0.1f, 10.0f, 0.1f }, 0.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("CHORUS_FEEDBACK", "Chorus Feedback", juce::NormalisableRange<float> { 0.f, 1.0f, 0.1f }, 0.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("CHORUS_MIX", "Chorus Mix", juce::NormalisableRange<float> { 0.f, 1.0f, 0.1f }, 0.1f));

    // Phaser
    params.push_back(std::make_unique<juce::AudioParameterFloat>("PHASER_DEPTH", "Phaser Depth", juce::NormalisableRange<float> { 0.f, 1.0f, 0.1f }, 0.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("PHASER_RATE", "Phaser Rate", juce::NormalisableRange<float> { 0.1f, 10.0f, 0.1f }, 0.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("PHASER_FEEDBACK", "Phaser Feedback", juce::NormalisableRange<float> { 0.f, 1.0f, 0.1f }, 0.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("PHASER_MIX", "Phaser Mix", juce::NormalisableRange<float> { 0.f, 1.0f, 0.1f }, 0.1f));

    return { params.begin(), params.end() };

}