#ifndef __LED_H__
#define __LED_H__

/* Dependecies */
#include "..\GPIO\GPIO.h"
#include "..\Time\Time.h"

/**
 * @brief LED class to control an LED.
 */
class LED
{
    public:
        /**
         * @brief Constructor for initializing an LED with a specified GPIO pin.
         * @param gpio Pointer to the `GPIO` object that will control the LED's state.
         */
        LED(GPIO* gpio); /**< Constructor for initializing the LED with a specific GPIO pin */

        /**
         * @brief Destructor for the LED object.
         */
        ~LED(); /**< Destructor for cleaning up the LED object */

        /**
         * @brief Initializes the LED with a single interval for both on and off times.
         * @param interval The total time (in milliseconds) for one complete on-off cycle of the LED. The on and off durations will be equal.
         * @return `uint8_t` Returns the result of the `begin` function that takes on and off times. A `1` indicates successful initialization, 
         *         while a `0` indicates the LED has already been initialized.
         */
        const uint8_t begin(const uint32_t interval);

        /**
         * @brief Initializes the LED with specified on and off times.
         * @param onTime The time (in milliseconds) for which the LED will stay on.
         * @param offTime The time (in milliseconds) for which the LED will stay off.
         * @return `uint8_t` Returns `1` for successful initialization, or `0` if the LED has already been initialized.
         */
        const uint8_t begin(const uint32_t onTime, const uint32_t offTime);

        /**
         * @brief Sets the LED's on and off times using a single interval.
         * @param interval The total time (in milliseconds) for one complete on-off cycle of the LED. The on and off durations will be equal.
         */
        void set(const uint32_t interval);

        /**
         * @brief Sets the on and off times for the LED behavior.
         * @param onTime The time (in milliseconds) for which the LED will stay on.
         * @param offTime The time (in milliseconds) for which the LED will stay off.
         */
        void set(const uint32_t onTime, const uint32_t offTime);

        /**
         * @brief Toggles the LED state based on the set on and off times.
         */
        void run(void);

        /**
         * @brief Ends the LED's operation and resets its state.
         * @return `uint8_t` Returns `1` for successful termination, or `0` if the LED was not initialized.
         */
        const uint8_t end(void);
        
    private:
        GPIO* gpio; /**< Pointer to the GPIO object */
        uint8_t began; /**< Flag to indicate if the LED implementation has begun */
        uint32_t onTime; /**< The on time in milliseconds */
        uint32_t offTime; /**< The off time in milliseconds */
        uint32_t nextTime; /**< The next time in milliseconds */
        uint32_t interval; /**< The interval in milliseconds */
};

#endif