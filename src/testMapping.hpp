#pragma once

#include "ofMain.h"

#ifndef ether
#define ether
#include "ofxEtherdream.h"
#endif

class testMapping : public ofBaseApp {  
  public:
		void setup();
		void draw();
  private:
    ofPoint triangleA[3];
    ofPoint triangleB[3];
};