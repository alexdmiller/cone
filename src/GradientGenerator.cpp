#include "GradientGenerator.hpp"

GradientGenerator::GradientGenerator() : Generator("gradient") {
  addParameter(innerColor.set("inner_color", ofColor(255), ofColor(0, 0, 0, 0), ofColor(255)));
  addParameter(outerColor.set("outer_color", ofColor(255), ofColor(0, 0, 0, 0), ofColor(255)));
};

void GradientGenerator::doDraw(Cone* cone, ofxIlda::Frame* ildaFrame) {
  cone->getUnmappedMesh()->clearColors();
  cone->getUnmappedMesh()->addColor(innerColor.get());
  
  for (int i = 1; i < cone->getUnmappedMesh()->getNumVertices(); i++) {
    ofVec3f p = cone->getUnmappedMesh()->getVertex(i);
    cone->getUnmappedMesh()->addColor(outerColor.get());
  }
  
  cone->getUnmappedMesh()->draw();
}

