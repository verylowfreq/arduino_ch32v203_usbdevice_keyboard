/** USB keyboard
 * 
 * Connection:
 *      (INPUT)  PA15, PB3, PB4, PB5: Pin--Switch--GND
 *      (OUTPUT) PA5, PA6, PA7 :     Pin--LED--GND
 * 
 * Key assign:
 *      PA15: 'w', PB4: 'a', PB5: 's', PA4: 'd'
 * 
 * LED of Keyboard status:
 *      PA5: CapsLock, PA6: Num, PA7: ScrollLock
 */

#include "USBD_Keyboard.h"

USBD_Keyboard Keyboard;


void setup() {
    // Configure the bitfield width of priority value.
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    // Init delay utils from WCH's code
    Delay_Init();

    // Start Serial port for debug
    Serial.begin(115200);
    Serial.println("Initializing...");
    Serial.println("USB keyboard demo with USBD");
    Serial.printf("SystemClk:%u\r\n", SystemCoreClock);

    // Init Status LED and blink
    pinMode(PA5, OUTPUT);
    for (int i = 0; i < 4; i++) {
        digitalWrite(PA5, HIGH);
        delay(500);
        digitalWrite(PA5, LOW);
        delay(500);
    }

    // Init USB Keyboard
    Keyboard.init();

    // Init GPIOs for key input
    pinMode(PA15, INPUT_PULLUP);
    pinMode(PB3, INPUT_PULLUP);
    pinMode(PB4, INPUT_PULLUP);
    pinMode(PB5, INPUT_PULLUP);

    // Init GPIOs for LED
    pinMode(PA5, OUTPUT);
    pinMode(PA6, OUTPUT);
    pinMode(PA7, OUTPUT);
}


void loop() {

    if (digitalRead(PA15) == LOW) {
        Keyboard.press(KEYCODE_W);
    } else {
        Keyboard.release(KEYCODE_W);
    }
    if (digitalRead(PB3) == LOW) {
        Keyboard.press(KEYCODE_A);
    } else {
        Keyboard.release(KEYCODE_A);
    }
    if (digitalRead(PB4) == LOW) {
        Keyboard.press(KEYCODE_S);
    } else {
        Keyboard.release(KEYCODE_S);
    }
    if (digitalRead(PB5) == LOW) {
        Keyboard.press(KEYCODE_D);
    } else {
        Keyboard.release(KEYCODE_D);
    }

    // Send keyboard input to Host
    Keyboard.apply();


    // Update LED status info
    Keyboard.fetch_led_status();

    // Update LED
    digitalWrite(PA5, Keyboard.led_capslock ? HIGH : LOW);
    digitalWrite(PA6, Keyboard.led_num ? HIGH : LOW);
    digitalWrite(PA7, Keyboard.led_scrolllock ? HIGH : LOW);
}
