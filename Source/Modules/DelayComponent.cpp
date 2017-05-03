#include "DelayComponent.h"

DelayParameters::DelayParameters(AudioProcessor& ap)
	:_ap(ap),
	channel(new AudioParameterInt("channel", "Channel", 0, 1, 0)),
	delayTime(new AudioParameterFloat("delayTime", "DelayTime", 0.f, 1.f, 0.5f)),
	mixing(new AudioParameterFloat("mixing", "Mixing", 0.f, 1.f, 1.f))
{
	_ap.addParameter(channel);
	_ap.addParameter(delayTime);
	_ap.addParameter(mixing);
}

DelayParameters::~DelayParameters() 
{}


//=======================================================================================================
DelayComponent::DelayComponent(int channel)
	:_channel(channel),
	delayBuffer(4800, 0.f)	//100 msec [fs = 48 kHz]
{
}

DelayComponent::~DelayComponent()
{}

void DelayComponent::setParams(DelayParameters& params) {
	if (_channel == params.getChannelVal()) {
		double fs = params.getSamplingRate();
		float d = params.getDelayTimeVal();

		delayTime_n = int(fs / 20.0 * d);
		if (delayTime_n >= delayBuffer.size()) {
			delayTime_n = delayBuffer.size() - 1;
		}

		mixing = params.getMixingVal();
	}
	else {
		delayTime_n = 0;
		mixing = 0.f;
	}
}

void DelayComponent::writeInDelayBuffer(float& audioBuffer) {
	delayBuffer.pop_front();
	delayBuffer.push_back(audioBuffer);
}

void DelayComponent::writeInEffectSignal(float& audioBuffer) {
	std::deque<float>::reverse_iterator itr = delayBuffer.rbegin();
	float dry = *itr;
	float wet = *(itr + delayTime_n);
	float mixed = mixing * wet + (1.f - mixing) * dry;

	audioBuffer = mixed;
}

//=======================================================================================================
DelayProcessor::DelayProcessor(DelayParameters& params)
	:_params(params)
{
	dDelayComponent.reserve(2);
	for (int n = 0; n < 2; n++) {
		dDelayComponent[n] = pDelayComponent(new DelayComponent(n));
	}
}

DelayProcessor::~DelayProcessor()
{}

void DelayProcessor::doProcessing(int channel, float& audioBuffer) {
	_params.setSamplingRate();
	dDelayComponent[channel]->setParams(_params);
	dDelayComponent[channel]->writeInDelayBuffer(audioBuffer);
	dDelayComponent[channel]->writeInEffectSignal(audioBuffer);
}