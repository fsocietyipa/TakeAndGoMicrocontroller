
#include "HX711.h"

HX711 scale;

float calibration_factor = -8.55; // this calibration factor is adjusted according to my load cell
float offset = -177000;
float units;
float ounces;

void setup() {
  Serial.begin(9600); 
  scale.begin(A1, A0);  // DT, CLK
  scale.set_scale();
  scale.tare();    // resetting value to 0
  scale.set_scale(calibration_factor);  // setting calibration
  scale.set_offset(offset);


}

void loop() { 
  Serial.print("Reading: ");
  /* taking average value of 10 measuerments */
  for(int i = 0;i < 10; i ++) {
    units =+ scale.get_units(), 10; 
  }
  units / 10;   
   
  ounces = units * 0.035274;    // converting ounces to gramms             
  Serial.print(ounces);         // printing value
  Serial.print(" grams");  
  Serial.println();
 
}
