/* Dependecies */
#include "LED.h"

LED::LED(volatile uint8_t* ddr, volatile uint8_t* dor, uint8_t bit)
{
	this->ddr = ddr;
	this->dor = dor;
	this->bit = bit;
}

LED::~LED()
{
	/* Empty */
}

void LED::begin(const uint32_t interval)
{
	this->begin(interval / 2, interval / 2);
}

void LED::begin(const uint32_t onTime, const uint32_t offTime)
{
	if (beginFunctionCalled)
		return;
	beginFunctionCalled = 1;

	/* Set data direction to output */
	IO.setMode(this->ddr, this->bit, OUTPUT);

	this->ledState = LOW;
	this->set(onTime, offTime);
}

void LED::set(const uint32_t interval)
{
	this->set(interval / 2, interval / 2);
}

void LED::set(const uint32_t onTime, const uint32_t offTime)
{
	this->onTime = onTime;
	this->offTime = offTime;
	this->interval = 0;
}

void LED::run(void)
{
	uint32_t currentTime = Time.milliseconds();

	if ((currentTime - this->previousTime) < this->interval)
		return;
	
	/* Check if led state is on */
	if (this->ledState)
		this->interval = this->offTime;
	else
		this->interval = this->onTime;

	/* Toggle the led state */
	this->ledState = !this->ledState;

	/* Set the led state */
	IO.write(this->dor, this->bit, this->ledState);

	this->previousTime = currentTime;
}

void LED::end(void)
{
	if (!beginFunctionCalled)
		return;
	beginFunctionCalled = 0;

	IO.setMode(this->ddr, this->bit, INPUT);

	this->ledState = LOW;
	this->set(0, 0);
}
