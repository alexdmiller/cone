//
//  ControllerThread.hpp
//  myInnocentSketch
//
//  Created by Alex on 12/8/17.
//
//

#ifndef ControllerThread_hpp
#define ControllerThread_hpp

#include <stdio.h>
#include "ofMain.h"

class ControllerThread : public ofThread {
  
public:
  void threadedFunction();
  int getKnob(int knob);
  bool getButton();
  
private:
  ofSerial serial;
  int knobs[7];
};

#endif /* ControllerThread_hpp */
