//
//  Bath.hpp
//  myInnocentSketch
//
//  Created by Alex on 1/27/18.
//
//

#ifndef Bath_hpp
#define Bath_hpp

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


#endif /* Bath_hpp */
