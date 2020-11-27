
#include "HX711.h"

HX711 scale;

float calibration_factor = -8.74; // this calibration factor is adjusted according to my load cell
float offset = -135000;
float units;
float ounces;

void setup() {
  Serial.begin(9600);
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");

  scale.begin(7, 4);  // DT, CLK
  scale.set_scale();
  scale.tare();    // resetting value to 0
  scale.set_scale(calibration_factor);  // setting calibration
  scale.set_offset(offset);

}

void loop() {

  scale.set_offset(offset);

  Serial.print("Reading: ");
  units = scale.get_units(), 10;
  if (units < 0)
  {
    units = 0.00;
  }
  ounces = units * 0.035274;
  Serial.print(ounces);
  Serial.print(" grams"); 
  Serial.print(" offset: ");
  Serial.print(offset);
  Serial.println();

  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      offset += 1000;
    else if(temp == '-' || temp == 'z')
      offset -= 1000;
  }
}
