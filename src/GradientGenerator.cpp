#include "GradientGenerator.hpp"

void GradientGenerator::draw(Cone* cone, ofxIlda::Frame* ildaFrame) {
  if (innerBrightness > 0 || outerBrightness > 0) {
    cone->getUnmappedMesh()->clearColors();
    cone->getUnmappedMesh()->addColor(ofFloatColor(1,1,1,innerBrightness));
    
    for (int i = 1; i < cone->getUnmappedMesh()->getNumVertices(); i++) {
      ofVec3f p = cone->getUnmappedMesh()->getVertex(i);
      cone->getUnmappedMesh()->addColor(ofFloatColor(1,1,1,outerBrightness));
    }
    
    cone->getUnmappedMesh()->draw();
  }
}

void GradientGenerator::onOscMessage(ofxOscMessage* message) {
  if (message->getAddress() == "/gradient/inner") {
    innerBrightness = message->getArgAsFloat(0);
  } else if (message->getAddress() == "/gradient/outer") {
    outerBrightness = message->getArgAsFloat(0);
  }
}
