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
/**
*/
class ShortDelayV2AudioProcessorEditor  
	: public AudioProcessorEditor, private Timer
{
public:
    ShortDelayV2AudioProcessorEditor (ShortDelayV2AudioProcessor&, DelayParameters& delayParams);
    ~ShortDelayV2AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ShortDelayV2AudioProcessor& processor;

	ChannelSection channelSection;
	DelayTimeSection delayTimeSection;
	MixingSection mixingSection;

	void timerCallback() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ShortDelayV2AudioProcessorEditor)
};
