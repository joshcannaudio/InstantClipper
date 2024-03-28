/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ClipperAudioProcessor::ClipperAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "Parameters", createParameters()),
                            audioVisualiser(1)
#endif
{
    audioVisualiser.setRepaintRate(30);
    audioVisualiser.setBufferSize(100);
}

ClipperAudioProcessor::~ClipperAudioProcessor()
{
}

//==============================================================================
const juce::String ClipperAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ClipperAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ClipperAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ClipperAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ClipperAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ClipperAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ClipperAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ClipperAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ClipperAudioProcessor::getProgramName (int index)
{
    return {};
}

void ClipperAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ClipperAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    audioProcessor.prepareToPlay(sampleRate);
    rmsLevelL.reset(sampleRate, 1.0f);
    rmsLevelR.reset(sampleRate, 1.0f);
    
    rmsLevelL.setCurrentAndTargetValue(-100.f);
    rmsLevelR.setCurrentAndTargetValue(-100.f);
    
    newInGain = Decibels::decibelsToGain(apvts.getRawParameterValue("Parameter1")->load());
    newOutGain = Decibels::decibelsToGain(apvts.getRawParameterValue("Parameter4")->load());
    
    audioVisualiser.clear();
}

void ClipperAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ClipperAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void ClipperAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    
    // Apply Input Gain to signal
    prevInGain = newInGain;
    newInGain = Decibels::decibelsToGain(apvts.getRawParameterValue("Parameter1")->load());
    buffer.applyGainRamp(0, buffer.getNumSamples(), prevInGain, newInGain);
    
    // apply processiong to audio signal
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    audioProcessor.process(buffer.getReadPointer(0),
                           buffer.getReadPointer(1),
                           buffer.getWritePointer(0),
                           buffer.getWritePointer(1),
                           buffer.getNumSamples(),
                           apvts,
                           buffer);
    
    // Apply Output Gain to signal
    prevOutGain = newOutGain;
    newOutGain = Decibels::decibelsToGain(apvts.getRawParameterValue("Parameter4")->load());
    buffer.applyGainRamp(0, buffer.getNumSamples(), prevOutGain, newOutGain);
    
    //Oscillascope
    audioVisualiser.pushBuffer(buffer);
    
    // gets rms values of audio post processing
    rmsLevelL.skip(buffer.getNumSamples());
    rmsLevelR.skip(buffer.getNumSamples());
    {
        const auto value = Decibels::gainToDecibels(buffer.getRMSLevel(0, 0, buffer.getNumSamples()));
        if(value < rmsLevelL.getCurrentValue())
            rmsLevelL.setTargetValue(value);
        else
            rmsLevelL.setCurrentAndTargetValue(value);
    }
    
    {
        const auto value = Decibels::gainToDecibels(buffer.getRMSLevel(1, 0, buffer.getNumSamples()));
        if(value < rmsLevelR.getCurrentValue())
            rmsLevelR.setTargetValue(value);
        else
            rmsLevelR.setCurrentAndTargetValue(value);
    }
}

//==============================================================================
bool ClipperAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ClipperAudioProcessor::createEditor()
{
    return new ClipperAudioProcessorEditor (*this);
}

//==============================================================================
void ClipperAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ClipperAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ClipperAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout ClipperAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
//    params.push_back (std::make_unique<AudioParameterFloat>(ParameterID { "Parameter1", 1}, "InputGain", -60.0f, 6.0f, 0.0f));
    
    // input gain
    params.push_back (std::make_unique<AudioParameterFloat>(ParameterID { "Parameter1", 1}, "InputGain", -24.0f, 24.0f, 0.0f));
    
    // drive
    params.push_back (std::make_unique<AudioParameterFloat>(ParameterID { "Parameter2", 2 }, "Drive", 0.0f, 100.0f, 0.0f));
    
    //clip threshold (Logarithmic)
    params.push_back (std::make_unique<AudioParameterFloat>(ParameterID { "Parameter3", 3 }, "Clip Threshold", juce::NormalisableRange<float>(-24.0f, 0.0f, 0.01f, 2.0f), -3.0f));
    
    // output gain
    params.push_back (std::make_unique<AudioParameterFloat>(ParameterID { "Parameter4", 4}, "OutputGain", -24.0f, 24.0f, 0.0f));
    
    params.push_back (std::make_unique<AudioParameterInt>(ParameterID { "Parameter5", 5}, "ClipType", 0, 2, 0));
    
    params.push_back (std::make_unique<AudioParameterFloat>(ParameterID { "Parameter6", 6}, "Shape", 0.0f, 25.0f, 0.0f));
    
    //RMS
//    params.push_back (std::make_unique<AudioParameterFloat>(ParameterID { "Parameter6", 6}, "RMSLeft", 6.0f, -60.0f, -60.0f));
    
    return { params.begin(), params.end() };
}

float ClipperAudioProcessor::getRmsValue(const int channel) const
{
    jassert(channel == 0 || channel == 1);
    if (channel == 0)
        return rmsLevelL.getCurrentValue();
    if (channel == 1)
        return rmsLevelR.getCurrentValue();
    return 0;
}
