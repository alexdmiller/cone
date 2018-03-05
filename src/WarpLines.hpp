#ifndef WarpLines_hpp
#define WarpLines_hpp

#include "Generator.hpp"
#include <stdio.h>

class WarpLines : public Generator {
public:
  WarpLines();
  void reset(bool & value);

protected:
  void doDraw(Cone* _cone, ofxIlda::Frame* _ildaFrame);
  
private:
  ofParameter<ofColor> color;
  ofParameter<float> speed;
  ofParameter<float> gap;
  ofParameter<float> step = 0.01;
  ofParameter<float> wavelength;
  ofParameter<bool> resetClock;
  
  float time;
};

#endif /* WarpLines_hpp */
