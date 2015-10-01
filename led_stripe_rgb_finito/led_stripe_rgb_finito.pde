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
