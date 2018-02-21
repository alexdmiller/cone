#ifndef PulseGenerator_hpp
#define PulseGenerator_hpp

#include <stdio.h>
#include "Generator.hpp"

class PulseGenerator : public Generator {
public:
  PulseGenerator();
  void draw(Cone* _cone, ofxIlda::Frame* _ildaFrame);
  void onPulse(bool & value);
  
private:
  vector<float> pulses;
  ofParameter<float> pulseSpeed = 1;
  ofParameter<ofColor> color;
  ofParameter<bool> pulse;
};

#endif /* PulseGenerator_hpp */
