/* Dependecies */
#include "LED.h"

/*!
 * @brief  LED constructor
 * @param  gpio
 *         The GPIO object
 */
LED::LED(GPIO* gpio)
{
	this->gpio = gpio;
}

/*!
 * @brief  LED destructor
 */
LED::~LED()
{
	this->gpio = NULL;
}

/*!
 * @brief  Begins the LED implementation using a fixed interval
 * @param  interval
 *         The interval of LED blink (example: for interval 1000 it will be 500 ms OFF and 500 ms ON)
 * @return True if was succesfull, otherwise false if already began
 */
void LED::begin(const uint32_t interval)
{
	return (this->begin(interval / 2, interval / 2));
}

/*!
 * @brief  Begins the LED implementation using separate on and off times
 * @param  onTime
 *         The interval of LED blink ON time
 * @param  offTime
 *         The interval of LED blink OFF time
 * @return True if was succesfull, otherwise false if already began
 */
void LED::begin(const uint32_t onTime, const uint32_t offTime)
{
	if (this->began)
		return (0);
	this->began = 1;

	Time.begin();
	this->gpio->setMode(OUTPUT);
	this->set(onTime, offTime);

	return (1);
}

/*!
 * @brief  Sets the LED blink interval
 * @param  interval
 *         The interval of LED blink (example: for interval 1000 it will be 500 ms OFF and 500 ms ON)
 */
void LED::set(const uint32_t interval)
{
	this->set(interval / 2, interval / 2);
}

/*!
 * @brief  Sets the LED blink on and off times
 * @param  onTime
 *         The interval of LED blink ON time
 * @param  offTime
 *         The interval of LED blink OFF time
 */
void LED::set(const uint32_t onTime, const uint32_t offTime)
{
	this->onTime = onTime;
	this->offTime = offTime;
	this->interval = 0;
}

/*!
 * @brief  Runs the LED implementation (no blocking as it uses timer for timekeeping)
 */
void LED::run(void)
{
	const uint32_t currentTime = Time.milliseconds();

	if ((currentTime - this->previousTime) < this->interval)
		return;

	this->interval = gpio->read() == HIGH ? offTime : onTime;
	this->gpio->write(TOGGLE);

	this->previousTime = currentTime;
}

/*!
 * @brief  Ends the LED implementation
 * @return True if was succesfull, otherwise false if did not began
 */
const uint8_t LED::end(void)
{
	if (!this->began)
		return (0);
	this->began = 0;

	this->gpio->setMode(INPUT);
	this->set(0, 0);

	return (1);
}
