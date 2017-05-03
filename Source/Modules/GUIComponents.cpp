#include "GUIComponents.h"

MyLabel::MyLabel(AudioProcessorEditor& ape, float fontSize, String text, Colour textC, Colour backC)
	:myLabel(text, text)
{
	ape.addAndMakeVisible(&myLabel);
	myLabel.setFont(Font(fontSize, Font::plain));
	myLabel.setColour(Label::textColourId, textC);
	myLabel.setColour(Label::backgroundColourId, backC);
	myLabel.setEditable(false, false, false);
}

MyLabel::~MyLabel()
{}

void MyLabel::setNewText(String newText){
	myLabel.setText(newText, dontSendNotification);
}

void MyLabel::display(int x, int y, int w, int h) {
	myLabel.setBounds(x, y, w, h);
}

//=====================================================================================================================
ChannelSection::ChannelSection(AudioProcessorEditor& ape, DelayParameters& delayParam)
	:_delayParam(delayParam), channelSlider("channelSlider"),
	mainLabel(ape, 16.0f, "Delay Channel", Colours::white, Colour(0x00000000)),
	subLabelLeft(ape, 13.0f, "L", Colours::white, Colour(0x00000000)),
	subLabelRight(ape, 13.0f, "R", Colours::white, Colour(0x00000000))
{
	ape.addAndMakeVisible(&channelSlider);
	channelSlider.setSliderStyle(Slider::LinearHorizontal);
	channelSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	channelSlider.setRange(0, 1, 1);
	channelSlider.setColour(Slider::thumbColourId, Colours::white);
	channelSlider.setColour(Slider::trackColourId, Colour(0x00000000));
	channelSlider.setColour(Slider::backgroundColourId, Colour(0x63ffffff));
	channelSlider.addListener(this);
}

ChannelSection::~ChannelSection()
{}

void ChannelSection::display() {
	channelSlider.setBounds(25, 29, 35, 24);
	mainLabel.display(5, 5, 100, 20);
	subLabelLeft.display(5, 28, 25, 23);
	subLabelRight.display(56, 28, 25, 23);
}

void ChannelSection::reflectHost() {
	float newVal = _delayParam.getChannelVal();

	if (newVal != channelSlider.getValue()) {
		channelSlider.setValue(newVal);
	}
}

void ChannelSection::sliderValueChanged(Slider* changedSlider) {
	if (changedSlider != &channelSlider) { return; }

	_delayParam.setChannelVal(channelSlider.getValue());
}

//=====================================================================================================================
DelayTimeSection::DelayTimeSection(AudioProcessorEditor& ape, DelayParameters& delayParam)
	:_delayParam(delayParam), valueSlider("delayTime"),
	mainLabel(ape, 16.f, "Delay Time", Colours::white, Colour(0x00000000)),
	valueLabel(ape, 13.f, String(0), Colours::black, Colours::white),
	valueUnitLabel(ape, 13.f, "ms", Colours::white, Colour(0x00000000))
{
	ape.addAndMakeVisible(&valueSlider);
	valueSlider.setSliderStyle(Slider::Rotary);
	valueSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	valueSlider.setRange(0, 1.f);
	valueSlider.setColour(Slider::thumbColourId, Colour(0x00000000));
	valueSlider.setColour(Slider::rotarySliderFillColourId, Colours::limegreen);
	valueSlider.setColour(Slider::rotarySliderOutlineColourId, Colours::white);
	valueSlider.addListener(this);
}

DelayTimeSection::~DelayTimeSection()
{}

void DelayTimeSection::display(){
	valueSlider.setBounds(0, 81, 59, 56);
	mainLabel.display(5, 60, 100, 20);
	valueLabel.display(58, 104, 30, 11);
	valueUnitLabel.display(86, 97, 25, 23);
}

void DelayTimeSection::reflectHost() {
	float newVal = _delayParam.getDelayTimeVal();

	if (newVal != valueSlider.getValue()) {
		valueSlider.setValue(newVal);
	}
}

void DelayTimeSection::sliderValueChanged(Slider *changedSlider) {
	if (changedSlider != &valueSlider) { return; }

	float newDelayTime = valueSlider.getValue();
	_delayParam.setDelayTimeVal(newDelayTime);

	int newDelayTime_ms = int(50.f * newDelayTime);
	valueLabel.setNewText(String(newDelayTime_ms));
}

//=====================================================================================================================
MixingSection::MixingSection(AudioProcessorEditor& ape, DelayParameters& delayParam)
	:_delayParam(delayParam), valueSlider("mixing"),
	mainLabel(ape, 16.f, "Mixing", Colours::white, Colour(0x00000000)),
	valueLabel(ape, 13.f, String(0), Colours::black, Colours::white),
	valueUnitLabel(ape, 13.f, "%", Colours::white, Colour(0x00000000))
{
	ape.addAndMakeVisible(&valueSlider);
	valueSlider.setSliderStyle(Slider::Rotary);
	valueSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	valueSlider.setRange(0, 1.f);
	valueSlider.setColour(Slider::thumbColourId, Colour(0x00000000));
	valueSlider.setColour(Slider::rotarySliderFillColourId, Colours::limegreen);
	valueSlider.setColour(Slider::rotarySliderOutlineColourId, Colours::white);
	valueSlider.addListener(this);
}

MixingSection::~MixingSection()
{}

void MixingSection::display(){
	valueSlider.setBounds(0, 162, 59, 56);
	mainLabel.display(5, 145, 100, 20);
	valueLabel.display(58, 187, 30, 11);
	valueUnitLabel.display(86, 181, 25, 23);
}

void MixingSection::reflectHost() {
	float newVal = _delayParam.getMixingVal();

	if (newVal != valueSlider.getValue()) {
		valueSlider.setValue(newVal);
	}
}

void MixingSection::sliderValueChanged(Slider *changedSlider) {
	if (changedSlider != &valueSlider) { return; }

	float newMixingVal = valueSlider.getValue();
	_delayParam.setMixingVal(newMixingVal);
	valueLabel.setNewText(String(int(newMixingVal * 100)));
}