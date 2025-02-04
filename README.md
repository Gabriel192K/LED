# LED
- LED library for basic LED control.

## Key features
- Compatible with `Microchip Studio IDE`.
- Easily configurable behaviour (interval blinking or onTime/offTime blinking).
- ```Set()``` function to dinamically configure the timings while running.
- Easy to use, just the ```run()``` function inside thr loop.
- Default LED state is `LOW`.

## Tested on
- ATmega328P @16MHz with `Microchip Studio IDE`.

## Example Code (Arduino)
```cpp
#include <GPIO.h>
#include <LED.h>

#define LED_DDR     &DDRB
#define LED_PORT    &PORTB
#define LED_PIN     &PINB
#define LED_BIT     5

GPIO led_gpio(LED_DDR, LED_PORT, LED_PIN, LED_BIT);
LED led(&led_gpio);

void setup() {
    // Begin LED with 1 second interval (500ms on, 500ms off)
    led.begin(1000);
}

void loop() {
    led.run();
}
```

## Example Code (Microchip Studio)
```cpp
#include <GPIO.h>
#include <LED.h>
#include <util/delay.h>

#define LED_DDR     &DDRB
#define LED_PORT    &PORTB
#define LED_PIN     &PINB
#define LED_BIT     5

int main(void) {
    GPIO led_gpio(LED_DDR, LED_PORT, LED_PIN, LED_BIT);
    LED led(&led_gpio);
    
    // Begin LED with different on/off times (200ms on, 800ms off)
    led.begin(200, 800);
    
    while(1) {
        led.run();
    }
    
    return 0;
}
```
