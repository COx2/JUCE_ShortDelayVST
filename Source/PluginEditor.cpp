/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
ShortDelayV2AudioProcessorEditor::ShortDelayV2AudioProcessorEditor (ShortDelayV2AudioProcessor& p, DelayParameters& delayParams)
    : AudioProcessorEditor (&p), processor (p),
	channelSection(*this, delayParams),
	delayTimeSection(*this, delayParams),
	mixingSection(*this, delayParams)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	setSize(110, 220);
	startTimer(30);
}

ShortDelayV2AudioProcessorEditor::~ShortDelayV2AudioProcessorEditor()
{
}

//==============================================================================
void ShortDelayV2AudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::black);

    //g.setColour (Colours::black);
    //g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void ShortDelayV2AudioProcessorEditor::resized()
{
	channelSection.display();
	delayTimeSection.display();
	mixingSection.display();
}

void ShortDelayV2AudioProcessorEditor::timerCallback() {
	channelSection.reflectHost();
	delayTimeSection.reflectHost();
	mixingSection.reflectHost();
}
