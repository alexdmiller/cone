#include "ShaderGenerator.hpp"

ShaderGenerator::ShaderGenerator() : Generator("shader") {
  shader.load("shaders/whispy");
}

void ShaderGenerator::doDraw(Cone* cone, ofxIlda::Frame* ildaFrame) {
  shader.begin();
  shader.setUniform1f("scale", ofGetMouseX());
  shader.setUniform1f("iTime", ofGetElapsedTimef());
  cone->getUnmappedMesh()->draw();
  shader.end();
}
