/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

#include "Modules\GUIcomponents.h"

//==============================================================================

class ShortDelayAudioProcessorEditor  
	: public AudioProcessorEditor, private Timer
{
public:
    ShortDelayAudioProcessorEditor (ShortDelayAudioProcessor& p, DelayParameters& delayParams);
    ~ShortDelayAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ShortDelayAudioProcessor& processor;

	ChannelSection channelSection;
	DelayTimeSection delayTimeSection;
	MixingSection mixingSection;
	
	void timerCallback() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ShortDelayAudioProcessorEditor)
};
