#pragma once

#include <cstdint>
#include <cstdbool>
#include <cstddef>


// USB Keycode (USB-HID Usage ID for Keyboard)

#define KEYCODE_W 0x1a
#define KEYCODE_A 0x04
#define KEYCODE_S 0x16
#define KEYCODE_D 0x07

extern volatile uint8_t KB_LED_Cur_Status;


class USBD_Keyboard {
public:
    constexpr static size_t HID_REPORT_LENGTH = 8;
    // HID report raw bytes. 
    uint8_t hidreport[HID_REPORT_LENGTH];
    bool led_num;
    bool led_capslock;
    bool led_scrolllock;

    void init();
    void press(uint8_t keycode);
    void release(uint8_t keycode);
    void apply();

    void fetch_led_status();
};
