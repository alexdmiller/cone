#include "ShaderGenerator.hpp"

ShaderGenerator::ShaderGenerator() : Generator("shader") {
  shader.load("shaders/test_shader");
}

void ShaderGenerator::doDraw(Cone* cone, ofxIlda::Frame* ildaFrame) {
  shader.begin();
  shader.setUniform1f("scale", scale);
  shader.setUniform1f("alpha", alpha);
  cone->getUnmappedMesh()->draw();
  shader.end();
}
