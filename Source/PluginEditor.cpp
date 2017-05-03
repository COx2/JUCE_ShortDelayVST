/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
ShortDelayAudioProcessorEditor::ShortDelayAudioProcessorEditor (ShortDelayAudioProcessor& p, DelayParameters& delayParams)
    : AudioProcessorEditor (&p), processor (p),
	channelSection(*this, delayParams),
	delayTimeSection(*this, delayParams),
	mixingSection(*this, delayParams)
{
    setSize (110, 220);
	startTimer(30);
}

ShortDelayAudioProcessorEditor::~ShortDelayAudioProcessorEditor()
{
}

//==============================================================================
void ShortDelayAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(Colours::black);

    //g.setColour (Colours::white);
    //g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void ShortDelayAudioProcessorEditor::resized()
{
	channelSection.display();
	delayTimeSection.display();
	mixingSection.display();
}

void ShortDelayAudioProcessorEditor::timerCallback() {
	channelSection.reflectHost();
	delayTimeSection.reflectHost();
	mixingSection.reflectHost();
}
