#ifndef GradientGenerator_hpp
#define GradientGenerator_hpp

#include <stdio.h>
#include "Generator.hpp"

class GradientGenerator : public Generator {
public:
  void draw(Cone* _cone, ofxIlda::Frame* _ildaFrame);
  void onOscMessage(ofxOscMessage* message);
  
private:
  float innerBrightness;
  float outerBrightness;
};


#endif /* GradientGenerator_hpp */
