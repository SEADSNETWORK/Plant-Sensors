#include "sensor.h"
#include "json.h"
#include "json.cpp"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void sensorSetup() {
  Serial.begin(9600);
 
  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
 
  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power 
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
}

StaticJsonDocument<200> sensorCode() {
   VL53L0X_RangingMeasurementData_t measure;
 
  Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
 
  // if (measure.RangeStatus != 4) {  // phase failures have incorrect data
  //   Serial.print("Distance (mm): "); Serial.println(measure.RangeMilliMeter);
  // } else {
  //   Serial.println(" out of range ");
  // }
 
  delay(100);

  RawData rawData[] = {
    {.dataType = "distance in mm", .value = measure.RangeMilliMeter}
  };

  const size_t n = sizeof(rawData) / sizeof(rawData[0]);

  std::array<RawData, n> convertedRawData;
  std::copy(std::begin(rawData), std::end(rawData), convertedRawData.begin());

  StaticJsonDocument<200> jsonData = convertToJson(convertedRawData);

  return jsonData;

}
