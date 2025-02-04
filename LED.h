#ifndef __LED_H__
#define __LED_H__

/* Dependecies */
#include "..\GPIO\GPIO.h"
#include "..\Time\Time.h"

/*!
 * @brief LED class to control an LED.
 */
class LED
{
    public:
        /*!
         * @brief Constructor: Initializes the LED object with the given GPIO.
         * @param gpio Pointer to the GPIO object
         */
        LED(GPIO* gpio);
        /*!
         * @brief Destructor: Cleans up the LED object.
         */
        ~LED();
        /*!
         * @brief Begins LED blinking with the given interval.
         * @param interval The interval in milliseconds
         * @return 1 if successful, 0 otherwise
         */
        const uint8_t begin(const uint32_t interval);
        /*!
         * @brief Begins LED blinking with the given on and off times.
         * @param onTime The on time in milliseconds
         * @param offTime The off time in milliseconds
         * @return 1 if successful, 0 otherwise
         */
        const uint8_t begin(const uint32_t onTime, const uint32_t offTime);
        /*!
         * @brief Sets the interval of the LED blinking.
         * @param interval The interval in milliseconds
         */
        void          set  (const uint32_t interval);
        /*!
         * @brief Sets the on and off times of the LED blinking.
         * @param onTime The on time in milliseconds
         * @param offTime The off time in milliseconds
         */
        void          set  (const uint32_t onTime, const uint32_t offTime);
        /*!
         * @brief Runs the LED implementation.
         */
        void          run  (void);
        /*!
         * @brief Stops the LED implementation.
         */
        const uint8_t end  (void);
    private:
        GPIO* gpio; /*!< Pointer to the GPIO object */
        uint8_t began; /*!< Flag to indicate if the LED implementation has begun */
        uint32_t onTime; /*!< The on time in milliseconds */
        uint32_t offTime; /*!< The off time in milliseconds */
        uint32_t nextTime; /*!< The next time in milliseconds */
        uint32_t interval; /*!< The interval in milliseconds */
};

#endif