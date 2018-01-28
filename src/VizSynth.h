//
//  VizSynth.h
//  myInnocentSketch
//
//  Created by Alex on 1/25/18.
//
//

#ifndef VizSynth_h
#define VizSynth_h

#include <stdio.h>
#include "Cone.hpp"
#include "ofxOsc.h"
#ifndef ether
#define ether
#include "ofxEtherdream.h"
#endif

class VizSynth {

public:
  virtual void draw(Cone* _cone, ofxIlda::Frame* _ildaFrame) {};
  virtual void onOscMessage(ofxOscMessage* message) {};
};

#endif /* VizSynth_h */
