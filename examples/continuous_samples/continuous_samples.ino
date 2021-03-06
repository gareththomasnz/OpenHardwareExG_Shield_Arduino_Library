/* reads samples from the OpenHardwareExG device */

#include <SPI.h>
#include <ADS129x.h>

void setup() {
  // Open serial communications
  Serial.begin(115200);

  // Initialize OpenHardwareExG board
  ADS129x.init();
}

void loop() {
    delay(1);
    Serial.print(millis() / 1000.0, 3); // seconds
    for (int chan = 1; chan <= 3; ++chan) {
      Serial.print("\t");
      Serial.print(ADS129x.getVolts(chan), 8);
    }
    Serial.println();
}
