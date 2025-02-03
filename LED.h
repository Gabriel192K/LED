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
        const uint8_t begin(const uint32_t interval);
        const uint8_t begin(const uint32_t onTime, const uint32_t offTime);
        void          set  (const uint32_t interval);
        void          set  (const uint32_t onTime, const uint32_t offTime);
        void          run  (void);
        const uint8_t end  (void);
    private:
        GPIO* gpio;
        uint8_t began;
        uint32_t onTime;
        uint32_t offTime;
        uint32_t previousTime;
        uint32_t interval;
};

#endif