#ifndef ShaderGenerator_hpp
#define ShaderGenerator_hpp

#include <stdio.h>
#include "Generator.hpp"

class ShaderGenerator : public Generator {
public:
  ShaderGenerator();
  
protected:
  void doDraw(Cone* _cone, ofxIlda::Frame* _ildaFrame);
  
private:
  ofShader shader;
  ofParameter<float> scale = 0;
  ofParameter<float> alpha = 0;
};

#endif /* ShaderGenerator_hpp */
