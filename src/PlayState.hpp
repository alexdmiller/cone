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
#include "VizSynth.h"
#include "ofxOsc.h"

#ifndef ether
#define ether
#include "ofxEtherdream.h"
#endif

class PlayState : public AppState {

public:
  PlayState(Cone* _cone, ofxIlda::Frame* _ildaFrame);
  void draw();
  void setMap(bool map);
  
protected:
  virtual void drawSynths();

  ofFbo canvas;
  ofxIlda::Frame* ildaFrame;
  Cone* cone;
  
private:
  vector<VizSynth*> synths;
  ofxOscReceiver receiver;
  bool map = true;
};

#endif /* PlayState_hpp */
