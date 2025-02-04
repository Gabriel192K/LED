/* Dependecies */
#include "LED.h"

/**
 * @brief Constructor for initializing an LED with a specified GPIO pin.
 * @details This constructor creates an `LED` object and associates it with a given GPIO pin. The `gpio` pointer is used to control 
 *          the state of the LED (e.g., turning it on or off) by accessing the specified GPIO pin. The LED's behavior will depend
 *          on the configuration of the GPIO pin (e.g., configured as an output).
 * @param gpio Pointer to the `GPIO` object that will control the LED's state.
 */
LED::LED(GPIO* gpio)
{
	this->gpio = gpio;
}

/**
 * @brief Destructor for the LED object.
 * @details This destructor is responsible for cleaning up the resources associated with the `LED` object. In this case, it sets 
 *          the `gpio` pointer to `NULL`, which effectively disassociates the LED from the GPIO pin it was using. This can be helpful 
 *          if you want to ensure the LED object is no longer referencing any GPIO pin after it is destroyed.
 * @note This destructor does not perform any additional cleanup, as there may not be any resources that need explicit release in this case.
 */
LED::~LED()
{
	this->gpio = NULL;
}

/**
 * @brief Initializes the LED with a single interval for both on and off times.
 * @details This function simplifies the initialization of the LED by accepting a single `interval` parameter, which is divided 
 *          by 2 to set both the on and off times equally. It then calls the `begin` function that takes separate on and off times 
 *          to initialize the LED.
 * @param interval The total time (in milliseconds) for one complete on-off cycle of the LED. The on and off durations will be equal.
 * @return `uint8_t` Returns the result of the `begin` function that takes on and off times. A `1` indicates successful initialization, 
 *         while a `0` indicates the LED has already been initialized.
 * @note This function provides a more convenient way to initialize the LED when the on and off times should be equal.
 */
const uint8_t LED::begin(const uint32_t interval)
{
	return (this->begin(interval / 2, interval / 2));
}

/**
 * @brief Initializes the LED with specified on and off times.
 * @details This function initializes the LED object by setting the GPIO pin mode to output, configuring the on and off times for 
 *          the LED's behavior, and starting the internal timekeeping. The initialization is only performed once, as the function 
 *          will return early if the LED has already been initialized.
 * @param onTime The time (in milliseconds) for which the LED will stay on.
 * @param offTime The time (in milliseconds) for which the LED will stay off.
 * @return `uint8_t` Returns `1` for successful initialization, or `0` if the LED has already been initialized.
 * @note This function should be called once during the setup phase to initialize the LED's behavior and its GPIO configuration.
 */
const uint8_t LED::begin(const uint32_t onTime, const uint32_t offTime)
{
	if (this->began)
		return (0);
	this->began = 1;

	Time.begin();
	this->gpio->setMode(OUTPUT);
	this->set(onTime, offTime);

	return (1);
}

/**
 * @brief Sets the LED's on and off times using a single interval.
 * @details This function configures the LED's on and off times by dividing the provided `interval` by 2, setting both the on 
 *          and off times to half of the specified interval. This allows the LED to blink with a frequency defined by the `interval` parameter.
 * @param interval The total time (in milliseconds) for one complete on-off cycle of the LED. The on and off durations will be equal.
 * @note This function simplifies the process of setting a constant blink rate by providing a single parameter instead of separate on/off times.
 */
void LED::set(const uint32_t interval)
{
	this->set(interval / 2, interval / 2);
}

/**
 * @brief Sets the on and off times for the LED behavior.
 * @details This function configures the timing for the LED's on and off states. The `onTime` and `offTime` parameters specify 
 *          the duration (in milliseconds) for which the LED will be on and off, respectively. The `interval` is reset to 0, and 
 *          `nextTime` is initialized to the `offTime`, ensuring that the LED starts in the off state.
 * @param onTime The time (in milliseconds) for which the LED will stay on.
 * @param offTime The time (in milliseconds) for which the LED will stay off.
 * @note This function is typically used to set up blinking behavior for the LED.
 */
void LED::set(const uint32_t onTime, const uint32_t offTime)
{
	this->onTime = onTime;
	this->offTime = offTime;
	this->interval = 0;
	this->nextTime = this->offTime;
}

/**
 * @brief Toggles the LED state based on the set on and off times.
 * @details This function checks the current time and toggles the LED's state (on/off) if the appropriate interval has passed. 
 *          It first checks if the current time has reached or exceeded the next toggle time. If so, the LED's state is toggled 
 *          between on and off, based on the current state of the GPIO pin (read as HIGH or LOW). The `nextTime` is then updated 
 *          to reflect when the LED should toggle again, based on the appropriate interval (either `onTime` or `offTime`).
 * @note This function should be called periodically (e.g., in the main loop) to maintain the LED's toggling behavior.
 */
void LED::run(void)
{
	const uint32_t currentTime = Time.milliseconds();

	if (currentTime < this->nextTime)
		return;

	this->interval = (gpio->read() == HIGH) ? offTime : onTime;
	this->gpio->write(TOGGLE);

	this->nextTime = currentTime + this->interval;
}

/**
 * @brief Ends the LED's operation and resets its state.
 * @details This function stops the LED's operation by resetting the `began` flag and setting the GPIO pin mode to INPUT, effectively 
 *          disabling the LED. The on and off times are also reset by calling `set(0, 0)`. The function returns `1` if the operation 
 *          was successful, or `0` if the LED was not previously initialized.
 * @return `uint8_t` Returns `1` for successful termination, or `0` if the LED was not initialized.
 * @note This function is used to clean up and stop the LED's operation, typically called when the LED is no longer needed.
 */
const uint8_t LED::end(void)
{
	if (*this->began)
		return (0);
	this->began = 0;

	this->gpio->setMode(INPUT);
	this->set(0, 0);

	return (1);
}
