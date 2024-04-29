/*
  ==============================================================================

    SynthVoice.h
    Created: 10 Apr 2024 3:04:59pm
    Author:  ant3b

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "Data/ADSRData.h"

class SynthVoice : public juce::SynthesiserVoice {
public:

    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples) override;

    void update(const float attack, const float decay, const float sustain, const float release);

private:

    ADSRData adsr;
    
    juce::AudioBuffer<float> synthBuffer;

    // return std::sin (x); // Sine Wave
    // return x / juce::MathConstants<float>::pi; // Saw Wave
    // return x < 0.f ? -1.f : 1.f; // Square Wave
    juce::dsp::Oscillator<float> osc{ [](float x) { return x / juce::MathConstants<float>::pi; } };
    juce::dsp::Gain<float> gain;
    bool isPrepared{ false };

};