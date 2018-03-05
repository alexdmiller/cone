#ifndef OutlineGenerator_hpp
#define OutlineGenerator_hpp

#include "Generator.hpp"
#include <stdio.h>

class OutlineGenerator : public Generator {
public:
  OutlineGenerator();
  
protected:
  void doDraw(Cone* _cone, ofxIlda::Frame* _ildaFrame);
  
private:
  ofParameter<ofColor> color;
  ofParameter<float> start;
  ofParameter<float> end;
  ofParameter<float> offset;
  ofParameter<float> spiral;
  ofParameter<float> speed;
};

#endif /* OutlineGenerator_hpp */
