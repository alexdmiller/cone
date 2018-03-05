#ifndef GradientGenerator_hpp
#define GradientGenerator_hpp

#include <stdio.h>
#include "Generator.hpp"

class GradientGenerator : public Generator {
public:
  GradientGenerator();
  
protected:
  void doDraw(Cone* _cone, ofxIlda::Frame* _ildaFrame);

private:
  ofParameter<ofColor> innerColor = ofColor(0, 0, 0, 0);
  ofParameter<ofColor> outerColor = ofColor(0, 0, 0, 0);
};


#endif /* GradientGenerator_hpp */
