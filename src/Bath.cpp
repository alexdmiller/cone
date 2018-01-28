//
//  Bath.cpp
//  myInnocentSketch
//
//  Created by Alex on 1/27/18.
//
//

#include "Bath.hpp"

void Bath::draw(Cone* cone, ofxIlda::Frame* ildaFrame) {
  cone->getUnmappedMesh()->clearColors();
  cone->getUnmappedMesh()->addColor(ofFloatColor(innerBrightness));
  
  for (int i = 1; i < cone->getUnmappedMesh()->getNumVertices(); i++) {
    ofVec3f p = cone->getUnmappedMesh()->getVertex(i);
    cone->getUnmappedMesh()->addColor(ofFloatColor(outerBrightness));
  }
  
  cone->getUnmappedMesh()->draw();
}

void Bath::onOscMessage(ofxOscMessage* message) {
  if (message->getAddress() == "/bath/inner") {
    innerBrightness = message->getArgAsFloat(0);
  } else if (message->getAddress() == "/bath/outer") {
    outerBrightness = message->getArgAsFloat(0);
  }
}
