//
//  PlayState.hpp
//  myInnocentSketch
//
//  Created by Alex on 12/4/17.
//
//

#ifndef PlayState_hpp
#define PlayState_hpp

#include <stdio.h>
#include "AppState.hpp"
#include "ofMain.h"
#include "Cone.hpp"
#include "ControllerThread.hpp"
#include "VizSynth.h"
#include "ofxOsc.h"

#ifndef ether
#define ether
#include "ofxEtherdream.h"
#endif

class PlayState : public AppState {

public:
  PlayState(Cone* _cone, ofxIlda::Frame* _ildaFrame, ControllerThread* _controller);
  void draw();
  void keyPressed(int key);
  void setMap(bool map);
  
private:
  void drawSynths();
  
  vector<VizSynth*> synths;
  ofFbo canvas;
  ofxIlda::Frame* ildaFrame;
  Cone* cone;
  ControllerThread* controller;
  bool map = true;
  int mode = 0;
  float t = 0;
  ofxOscReceiver receiver;
};

#endif /* PlayState_hpp */
