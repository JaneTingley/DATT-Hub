/**
 * Built on oscP5parsing by andreas schlegel, from the OscP5 library examples
 * requires the OscP5 library
 */

import oscP5.*;
import netP5.*;

float x, y, targetX, targetY;

OscP5 oscP5;
NetAddress myRemoteLocation;

void setup() {
  size(400,400);
  frameRate(25);
  
  /* start oscP5, listening for incoming messages at port 8000 */
  oscP5 = new OscP5(this,8000);
  
  noStroke();
  background(218, 123, 240);
}

void draw() {
  // targetX and targetY are updated in void oscEvent.
  // First, apply some smoothing (look up "easing" for more info)
  x = x + (targetX - x) * .2;
  y = y + (targetY - y) * .2;

  // fade the trails by overlaying the background colour with transparency
  fill(218, 123, 240, 30);
  rect(0, 0, width, height);

  // Draw an ellipse
  fill(255, 255, 0);
  ellipse (x, y, 20, 20);
}

void oscEvent(OscMessage theOscMessage) {
  /* check if theOscMessage has the address pattern we are looking for (accelerometer). */
  if(theOscMessage.checkAddrPattern("/accxyz")==true) {
    /* check if the typetag is the right one (3 floats).*/
    if(theOscMessage.checkTypetag("fff")) {
      /* parse theOscMessage and extract the values from the osc message arguments. */
      // Use two of the three values for x & y
      targetX = (theOscMessage.get(0).floatValue() + 1) / 2 * width;
      targetY = (theOscMessage.get(1).floatValue() + 1) / 2 * height;
      println(x);
      return;
    }  
  } 
}
