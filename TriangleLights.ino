#include "SPI.h"
#include "Adafruit_WS2801.h"

#define DEBUG_LEVEL DEBUG_HIGH
#include "Debug.h"

#include "GeneralUtils.h"
#include "PixelUtil.h"

#include "TriangleStructure.h"
#include "TriangleLights.h"

int numLeds = 50;
PixelUtil pixels;

int numTriangles = 0;
Triangle *triangles;

void setup()
{
  Serial.begin(9600);
  DEBUG_PRINTLN(DEBUG_HIGH, "Initializing");

  randomSeed(analogRead(3));

  pixels = PixelUtil(numLeds, 12, 11);

  /* Setup the sensors */
  initializePins();

  /* Generate the geometry */
  triangles = buildIcosohedron();
  numTriangles = 20;

  //  DEBUG_PRINTLN(DEBUG_HIGH, "Early exit"); return; // XXX

  /* Set the pixel values for the triangles */
  int led = numLeds - 1;
  for (int i = 0; i < numTriangles; i++) {
    // XXX - There is no intelligence here.  This is done from highest down
    // so that when wiring the end led should be placed first.
    if (led >= 2) {
      DEBUG_VALUE(DEBUG_HIGH, "Setting leds for tri:", i);
      DEBUG_VALUE(DEBUG_HIGH, " ", led);
      DEBUG_VALUE(DEBUG_HIGH, " ", led - 1);
      DEBUG_VALUELN(DEBUG_HIGH, " ", led - 2);

      triangles[i].setLedPixels(led, led - 1, led - 2);
      led -= 3;
    } else {
      DEBUG_VALUELN(DEBUG_HIGH, "No leds for tri:", i);
    }
  }
}

#define NUM_MODES 2
#define MODE_PERIOD 50
void loop() {
  return;

  /* Check for update of light sensor value */
  sensor_photo();

  int mode = getButtonValue() % NUM_MODES;

  switch (mode) {
  case 0: trianglesTestPattern(triangles, numTriangles, 500);
  case 1: trianglesTestPattern(triangles, numTriangles, 500);
  }
  //pixels.update();

  delay(10);
}
