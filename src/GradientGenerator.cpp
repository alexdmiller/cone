#include "GradientGenerator.hpp"

void GradientGenerator::draw(Cone* cone, ofxIlda::Frame* ildaFrame) {
  cone->getUnmappedMesh()->clearColors();
  cone->getUnmappedMesh()->addColor(ofFloatColor(innerBrightness));
  
  for (int i = 1; i < cone->getUnmappedMesh()->getNumVertices(); i++) {
    ofVec3f p = cone->getUnmappedMesh()->getVertex(i);
    cone->getUnmappedMesh()->addColor(ofFloatColor(outerBrightness));
  }
  
  cone->getUnmappedMesh()->draw();
}

void GradientGenerator::onOscMessage(ofxOscMessage* message) {
  if (message->getAddress() == "/gradient/inner") {
    innerBrightness = message->getArgAsFloat(0);
  } else if (message->getAddress() == "/gradient/outer") {
    outerBrightness = message->getArgAsFloat(0);
  }
}
