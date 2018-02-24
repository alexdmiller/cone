#include "GradientGenerator.hpp"

GradientGenerator::GradientGenerator() : Generator("gradient") {
  addParameter(innerBrightness.set("inner_brightness", 0, 0, 1));
  addParameter(outerBrightness.set("outer_brightness", 0, 0, 1));
};

void GradientGenerator::doDraw(Cone* cone, ofxIlda::Frame* ildaFrame) {
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

