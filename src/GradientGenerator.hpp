#ifndef GradientGenerator_hpp
#define GradientGenerator_hpp

#include <stdio.h>
#include "Generator.hpp"

class GradientGenerator : public Generator {
public:
  GradientGenerator();
  void draw(Cone* _cone, ofxIlda::Frame* _ildaFrame);
  void onOscMessage(ofxOscMessage* message);

private:
  ofParameter<float> innerBrightness = 0;
  ofParameter<float> outerBrightness = 0;
};


#endif /* GradientGenerator_hpp */
