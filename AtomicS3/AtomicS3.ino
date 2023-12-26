#include <M5AtomS3.h>
#include <TinyGPSPlus.h>

TinyGPSPlus gps;

// From example code: Delay while ensuring that we're listening from the GPS over UART.
static void smartDelay(unsigned long ms) {
    unsigned long start = millis();
    do {
        while (Serial2.available()) gps.encode(Serial2.read());
    } while (millis() - start < ms);
}

// Super basic setup, not using any AtomS3 display awesomeness
void setup() {
    auto cfg = M5.config();
    M5.begin(cfg);
    Serial2.begin(9600, SERIAL_8N1, 5, -1);
}

void loop() {
    // Delay first and read from GPS
    smartDelay(1000);
    // Clear the display and show what we've got.
    M5.Lcd.clear();
    M5.Lcd.setCursor(0,0);
    M5.Lcd.printf("lat: %0.4f\nlon: %0.4f\n", gps.location.lat(), gps.location.lng());
    M5.Lcd.printf("%i satellites", gps.satellites.value());
}
