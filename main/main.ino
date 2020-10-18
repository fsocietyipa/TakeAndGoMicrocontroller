
#include "HX711.h"

struct ScaleData {
  float calibrationFactor;
  float offset;
  int sckPin;
  int dtPin;
  float units;
  float ounces;
  HX711 scale;
};

int scalesAmount = 5;

ScaleData scalesArray [scalesAmount] = {
  { -8.55, -172000, 6, 5, 0, 0 },
  { -8.8, -30000, 11, 10, 0, 0 }, 
  { -8.48, -281000, A0, A1, 0, 0 },
  { -8.97, -135000, A4, A5, 0, 0 }, 
  { -8.75, -218000, A2, A3, 0, 0 }
};

void setup() {
  Serial.begin(9600); 
  for (int i = 0; i < scalesAmount; i++) {
    ScaleData scaleElement = scalesArray[i];
    scaleElement.scale.begin(scaleElement.dtPin, scaleElement.sckPin);
    scaleElement.scale.set_scale();
    scaleElement.scale.tare();    // resetting value to 0
    scaleElement.scale.set_scale(scaleElement.calibrationFactor);  // setting calibration
    scaleElement.scale.set_offset(scaleElement.offset);
    scalesArray[i] = scaleElement;
  }
}

void loop() { 
  /* loop to read average value */
  for (int i = 0; i < scalesAmount; i++) {
    ScaleData scaleElement = scalesArray[i];
    /* taking average value of 10 measuerments */
    for(int i = 0; i < 10; i++) {
      scaleElement.units =+ scaleElement.scale.get_units(), 10; 
    }
    scaleElement.units / 10;   
    scaleElement.ounces = scaleElement.units * 0.035274;    // converting ounces to gramms             
    scalesArray[i] = scaleElement;
  }
  /* loop to print scale values */
  for (int i = 0; i < scalesAmount; i++) {
    ScaleData scaleElement = scalesArray[i];
    Serial.print("index ");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(scaleElement.ounces);         // printing value
    Serial.print(" grams, ");  
  }
  Serial.println();

}
