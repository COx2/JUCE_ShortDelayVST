#pragma once

#include "JuceHeader.h"
#include "DelayComponent.h"

#include <vector>
#include <memory>

class MyLabel {
public:
	MyLabel(AudioProcessorEditor& ape, float fontSize, String text, Colour textC, Colour backC);
	~MyLabel();

	void setNewText(String newText);
	void display(int x, int y, int w, int h);

private:
	Label myLabel;
};

//==========================================================================================================
class ChannelSection : private Slider::Listener 
{
public:
	ChannelSection(AudioProcessorEditor& ape, DelayParameters& delayParam);
	~ChannelSection();

	void display();
	void reflectHost();

private:
	DelayParameters& _delayParam;
	Slider channelSlider;
	MyLabel mainLabel;
	MyLabel subLabelLeft;
	MyLabel subLabelRight;

	void sliderValueChanged(Slider *changedSlider) override;
};

class DelayTimeSection : private Slider::Listener
{
public:
	DelayTimeSection(AudioProcessorEditor& ape, DelayParameters& delayParam);
	~DelayTimeSection();

	void display();
	void reflectHost();

private:
	DelayParameters& _delayParam;
	Slider valueSlider;
	MyLabel mainLabel;
	MyLabel valueLabel;
	MyLabel valueUnitLabel;

	void sliderValueChanged(Slider *changedSlider) override;
};

class MixingSection : private Slider::Listener
{
public:
	MixingSection(AudioProcessorEditor& ape, DelayParameters& delayParam);
	~MixingSection();

	void display();
	void reflectHost();

private:
	DelayParameters& _delayParam;
	Slider valueSlider;
	MyLabel mainLabel;
	MyLabel valueLabel;
	MyLabel valueUnitLabel;

	void sliderValueChanged(Slider *changedSlider) override;
};