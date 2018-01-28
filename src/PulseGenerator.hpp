//
//  Pulser.hpp
//  myInnocentSketch
//
//  Created by Alex on 1/25/18.
//
//

#ifndef Pulser_hpp
#define Pulser_hpp

#include <stdio.h>
#include "Generator.hpp"

class PulseGenerator : public Generator {
public:
  void draw(Cone* _cone, ofxIlda::Frame* _ildaFrame);
  void onOscMessage(ofxOscMessage* message);

private:
  vector<float> pulses;
  float pulseSpeed = 1;
  ofColor color;
};

#endif /* Pulser_hpp */
