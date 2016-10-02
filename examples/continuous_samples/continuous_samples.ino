/* reads samples from the OpenHardwareExG device */

#include <SPI.h>
#include <ADS129x.h>

void setup() {
  // Open serial communications and wait for port to open:
  //  Serial.begin(230400);
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // Initialize OpenHardwareExG board
  ADS129x.init();
  Serial.print("chip ID: ");
  Serial.println(ADS129x.chipId());
}

unsigned long loop_counter = 0;
unsigned long time_last_sample = 0; // microseconds
void loop() {
  ++loop_counter;

  // if new data
  if (ADS129x.timeOfSample() != time_last_sample) {
    time_last_sample = ADS129x.timeOfSample();
    Serial.print((time_last_sample * 1.0) / (1000 * 1000), 6);
    for (int chan = 1; chan <= 8; ++chan) {
      Serial.print("\t");
      Serial.print(ADS129x.getVolts(chan), 8);
    }
    Serial.println();
  } else {
    if (0 == (loop_counter % (1024 * 1024))) {
      Serial.print("sample count: ");
      Serial.print(ADS129x.sampleCount());
      Serial.println(" (waiting)");
    }
  }
}
