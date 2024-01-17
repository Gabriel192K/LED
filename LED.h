#ifndef __LED_H__
#define __LED_H__

/* Dependecies */
#include "..\Time\Time.h"
#include "..\IO\IO.h"

class LED
{
    public:
        LED(volatile uint8_t* ddr, volatile uint8_t* dor, uint8_t bit);
        ~LED();
        void begin(const uint32_t interval);
        void begin(const uint32_t onTime, const uint32_t offTime);
        void set  (const uint32_t interval);
        void set  (const uint32_t onTime, const uint32_t offTime);
        void run  (void);
        void end  (void);
    private:
        volatile uint8_t* ddr;
        volatile uint8_t* dor;
        uint8_t bit;
        uint8_t beginFunctionCalled;
        uint32_t onTime;
        uint32_t offTime;
        uint32_t previousTime;
        uint32_t interval;
        uint8_t ledState;
};

#endif