#ifndef ShaderGenerator_hpp
#define ShaderGenerator_hpp

#include <stdio.h>
#include "Generator.hpp"

class ShaderGenerator : public Generator {
public:
  ShaderGenerator();
  void draw(Cone* _cone, ofxIlda::Frame* _ildaFrame);
  
private:
  ofShader shader;
};

#endif /* ShaderGenerator_hpp */
