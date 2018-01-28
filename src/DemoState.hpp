//
//  PlayState.hpp
//  myInnocentSketch
//
//  Created by Alex on 12/4/17.
//
//

#ifndef DemoState_hpp
#define DemoState_hpp

#include <stdio.h>
#include "AppState.hpp"
#include "ofMain.h"
#include "Cone.hpp"
#include "VizSynth.h"
#include "ofxOsc.h"
#include "PlayState.hpp"

#ifndef ether
#define ether
#include "ofxEtherdream.h"
#endif

class DemoState : public PlayState {

public:
  DemoState(Cone* _cone, ofxIlda::Frame* _ildaFrame, bool _map) : PlayState(_cone, _ildaFrame, _map) {};
  
private:
  void drawSynths();
  int mode = 0;
  float t = 0;
};

#endif /* PlayState_hpp */
