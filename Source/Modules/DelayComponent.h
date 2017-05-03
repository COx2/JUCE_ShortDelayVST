#pragma once

#include "JuceHeader.h"
#include <memory>
#include <deque>
#include <vector>

class DelayParameters {
public:
	DelayParameters(AudioProcessor& ap);
	~DelayParameters();

	double getSamplingRate() { return samplingRate; };
	int getChannelVal() { return channel->get(); };
	float getDelayTimeVal() { return delayTime->get(); };
	float getMixingVal() { return mixing->get(); };

	void setSamplingRate() { samplingRate = _ap.getSampleRate(); };
	void setChannelVal(int newVal) { channel->setValueNotifyingHost(newVal); };
	void setDelayTimeVal(float newVal) { delayTime->setValueNotifyingHost(newVal); };
	void setMixingVal(float newVal) { mixing->setValueNotifyingHost(newVal); };

private:
	AudioProcessor& _ap;
	double samplingRate = 48000.0;
	AudioParameterInt* channel;
	AudioParameterFloat* delayTime;
	AudioParameterFloat* mixing;
};

class DelayComponent {
public:
	DelayComponent(int channel);
	~DelayComponent();

	void setParams(DelayParameters& params);
	void writeInDelayBuffer(float& audioBuffer);
	void writeInEffectSignal(float& audioBuffer);

private:;
	int _channel;
	std::deque<float> delayBuffer;
	int delayTime_n;
	float mixing;
};

class DelayProcessor {
public:
	DelayProcessor(DelayParameters& params);
	~DelayProcessor();

	void doProcessing(int channel, float& audioBuffer);

private:
	DelayParameters& _params;
	typedef std::unique_ptr<DelayComponent> pDelayComponent;
	std::vector<pDelayComponent> dDelayComponent;
};