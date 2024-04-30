#ifndef __LED_H__
#define __LED_H__

/* Dependecies */
#include "..\GPIO\GPIO.h"
#include "..\Time\Time.h"

class LED
{
    public:
        LED(GPIO* gpio);
        ~LED();
        void begin(const uint32_t interval);
        void begin(const uint32_t onTime, const uint32_t offTime);
        void set  (const uint32_t interval);
        void set  (const uint32_t onTime, const uint32_t offTime);
        void run  (void);
        void end  (void);
    private:
        GPIO* gpio;
        uint8_t beginFunctionCalled;
        uint32_t onTime;
        uint32_t offTime;
        uint32_t previousTime;
        uint32_t interval;
};

#endif