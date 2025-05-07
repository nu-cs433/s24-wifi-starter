#include <Arduino.h> // Required for all code


/*~~~~~Hardware Definitions~~~~~*/
// These are hardware specific to the Heltec WiFi LoRa 32 V3
// Cite: https://resource.heltec.cn/download/WiFi_LoRa_32_V3/HTIT-WB32LA(F)_V3.1_Schematic_Diagram.pdf
#define PRG_BUTTON 0
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Flag for whether the button was recently pressed
static volatile bool buttonFlag = false;

// This function should be called automatically when a button is pressed.
//  It is placed in RAM to avoid Flash usage errors
#if defined(ESP8266) || defined(ESP32)
  ICACHE_RAM_ATTR
#endif
void buttonISR(void)
{
    // WARNING:  No Flash memory may be accessed from the IRQ handler: https://stackoverflow.com/a/58131720
    //  So don't call any functions or really do anything except change the flag
    buttonFlag = true;
}


// Setup, code starts here and runs this function once
void setup()
{
    // Initialize serial communications
    Serial.begin(115200);

    // Enable LED
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);

    // Set up GPIO pin for "PRG" button and enable interrupts for it
    pinMode(PRG_BUTTON, INPUT);
    attachInterrupt(PRG_BUTTON, buttonISR, FALLING);

    Serial.println("Setup done");
}

// Loop, after setup, this function is called repeatedly
void loop()
{
    // Loop runs as fast as it can
    // And we don't want delays in here, or else other checks will be delayed
    // So, we'll use an event-loop technique to determine when a second has passed
    // If you want some actions to happen with a time delay, use this technique
    // Note: `static` local variables are only initialized once at boot
    static unsigned long next_time = millis(); // always run the first time
    if (millis() > next_time) {
        next_time += 1000; // next time will be one second later

        // periodic actions here

        // Toggle the LED state
        static uint8_t state = LOW;
        digitalWrite(LED, state);
        if (state == LOW) {
            state = HIGH;
        } else {
            state = LOW;
        }
        Serial.printf("Toggled LED\n");
    }

    // Handle button presses
    if (buttonFlag) {
        buttonFlag = false;
        Serial.printf("Pressed a button!\n");
    }
}
