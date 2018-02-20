#include "ShaderGenerator.hpp"

ShaderGenerator::ShaderGenerator() : Generator("shader") {
  shader.load("shaders/test_shader");
}

void ShaderGenerator::draw(Cone* cone, ofxIlda::Frame* ildaFrame) {
  shader.begin();
  shader.setUniform1f("scale", ofGetMouseX());
  cone->getUnmappedMesh()->draw();
  shader.end();
}

void ShaderGenerator::onOscMessage(ofxOscMessage* message) {

}
