#include "USBD_Keyboard.h"

#include <cstring>

#include "src/USB-Device-Keyboard/hw_config.h"
#include "src/USB-Driver/inc/usb_lib.h"
#include "src/USB-Device-Keyboard/usb_desc.h"
#include "src/USB-Device-Keyboard/usb_pwr.h"
#include "src/USB-Device-Keyboard/usb_prop.h"
#include "src/USB-Device-Keyboard/hw_config.h"

// usb_endp.c
extern "C" {
    uint8_t USBD_ENDPx_DataUp( uint8_t endp, uint8_t *pbuf, uint16_t len );
}

void USBD_Keyboard::init() {
    // Clear HID report buffer
    memset(this->hidreport, 0x00, this->HID_REPORT_LENGTH);
    // Clear LEDs status
    this->led_num = false;
    this->led_capslock = false;
    this->led_scrolllock = false;

    // Init USB function

    // Configure clock for USB function
    Set_USBConfig();
    // Configure USB keyboard
    USB_Init();
    // Configure interrupts for USB function
    USB_Interrupts_Config();
}

void USBD_Keyboard::press(uint8_t keycode) {
    for (size_t i = 2; i < this->HID_REPORT_LENGTH; i++) {
        if (this->hidreport[i] == keycode) {
            // Already pressed
            return;
        } else if (this->hidreport[i] == 0) {
            // Found a empty byte. Use it.
            this->hidreport[i] = keycode;
            return;
        }
    }
    // Failed to add keycode
    return;
}

void USBD_Keyboard::release(uint8_t keycode) {
    for (size_t i = 2; i < this->HID_REPORT_LENGTH; i++) {
        if (this->hidreport[i] == keycode) {
            // Found the byte. Clear it.
            this->hidreport[i] = 0;
            return;
        }
    }
    // Not found
    return;
}

void USBD_Keyboard::apply() {
    if (bDeviceState != CONFIGURED) {
        // USB not connected and/or configured correctly.
        return;
    }

    // Copy our HID Report buffer to USB endpoint 1 and request to send
    uint8_t status = USBD_ENDPx_DataUp(ENDP1, this->hidreport, this->HID_REPORT_LENGTH);
    if (status == USB_SUCCESS) {
        // OK
        return;
    } else { // == USB_ERROR
        // Error. Previous data was not sent yet.
        return;
    }
}

void USBD_Keyboard::fetch_led_status() {
    // Variable "KB_LED_Cur_Status" is updated at USB interurpt routine.
    this->led_num = (KB_LED_Cur_Status & 0x01) != 0;
    this->led_capslock = (KB_LED_Cur_Status & 0x02) != 0;
    this->led_scrolllock = (KB_LED_Cur_Status & 0x04) != 0;
}
