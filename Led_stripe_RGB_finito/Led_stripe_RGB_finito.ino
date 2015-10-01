
#include <PololuLedStrip.h>

// Create an ledStrip object and specify the pin it will use.
PololuLedStrip<6> ledStrip;

// Create a buffer for holding the colors (3 bytes per color).
#define LED_COUNT 300
rgb_color colors[LED_COUNT];


String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

int red;
int green;
int blue;
	
void setup()
{
  // Start up the serial port, for communication with the PC.
  Serial.begin(57600);
  //Serial.println("Ready to receive colors.");
  inputString.reserve(24);
}

void loop()
{
  // If any digit is received, we will go into integer parsing mode
  // until all three calls to parseInt return an interger or time out.
  serialEvent(); //call the function
  // print the string when a newline arrives:
  if (stringComplete) {
      // Read the color from the computer.
      rgb_color color;
      rgb_color colordark;
      colordark.red = 0;
      colordark.green = 0;
      colordark.blue = 0;
      
      color.red = getValue(inputString, ';', 0).toInt();
      color.green = getValue(inputString, ';', 1).toInt();
      color.blue = getValue(inputString, ';', 2).toInt();
      int position = getValue(inputString, ';', 3).toInt();
	  colors[position] = color;
	  colors[position+1] = color;
	  colors[position-1] = color;
	  colors[position-2] = color;
	  colors[position-3] = color;
	  colors[position-4] = color;
	  colors[position-5] = color;
	  colors[position-6] = color;
	  colors[position-7] = color;
	  colors[position-8] = color;
	  colors[position-9] = color;
	  colors[position-10] = color;
   	  colors[0] = (rgb_color) {0,0,0};
	 
	  inputString = "";
	  stringComplete = false;
    }
           // Update the colors buffer.
      for(int i = 0; i < LED_COUNT; i++)
      {
      		
      		red = colors[i].red;
      		green = colors[i].green;
      		blue = colors[i].blue;
      		
      		if (red > 0) {
      			colors[i].red = red-5;
      			}
      		if (green > 0) {
      			colors[i].green = green-5;
      			}
      		if (blue > 0) {
      			colors[i].blue = blue-5;
      			}
      			
      }
      delay(30);
	  // Write the colors to the LED strip.
	  ledStrip.write(colors, LED_COUNT);
  }
  

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == 'w') {
      stringComplete = true;
    }
  }
}


String getValue(String data, char separator, int index)
{
 int found = 0;
  int strIndex[] = {
0, -1  };
  int maxIndex = data.length()-1;
  for(int i=0; i<=maxIndex && found<=index; i++){
  if(data.charAt(i)==separator || i==maxIndex){
  found++;
  strIndex[0] = strIndex[1]+1;
  strIndex[1] = (i == maxIndex) ? i+1 : i;
  }
 }
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}


/* PROCESSING

import gab.opencv.*;
import processing.video.*;
import processing.serial.*;

OpenCV opencv;
Capture video;


Serial myPort;  // Create object from Serial class


void setup() {
  size(640, 480);
  video = new Capture(this, width, height);
  video.start(); 
  opencv = new OpenCV(this, 640, 480);
  
  opencv.startBackgroundSubtraction(5, 3, 0.5);
  
  String portNames[] = Serial.list();
  String portName = portNames[0];
  println(portNames);
  
  myPort = new Serial(this, "/dev/ttyUSB0", 57600);
  
}

void draw() {
  if (video.available()) {
    video.read();
    video.loadPixels();
    image(video, 0, 0);  
    opencv.loadImage(video);
    
    opencv.updateBackground();
    
    opencv.dilate();
    opencv.erode();
  
    noFill();
    stroke(255, 0, 0);
    strokeWeight(3);
    for (Contour contour : opencv.findContours()) {
      contour.draw();
    }
    video.loadPixels(); 
    for (int i = 0; i < 640; i++) {
      color c = get(i,180);
      int r=(c>>16)&255;
      int g=(c>>8)&255;
      int b=c&255; 
        // Set pixel at that location to random color
        if (r == 255){
          
          delay(10);
          //println(i);
          float m = map(i, 0, width, 0, 250);
          //println(m);
          int x = 251 - int(m);
          myPort.write("255;0;0;" + x + ";w");           // send mouse position  
          break;
      }
    }
  }
}
*/
