#include "OutlineGenerator.hpp"

OutlineGenerator::OutlineGenerator() : Generator("outline") {
  addParameter(color.set("color", ofColor(255), ofColor(0, 0, 0, 0), ofColor(255)));
  addParameter(start.set("start", 0, 0, 2));
  addParameter(end.set("end", 0.5, 0, 2));
  addParameter(offset.set("offset", 0, -3, 3));
  addParameter(spiral.set("spiral", 0, 0, 2));
};

void OutlineGenerator::doDraw(Cone* cone, ofxIlda::Frame* ildaFrame) {
  ofSetColor(color);
  for (int i = 1; i < cone->getUnmappedMesh()->getNumVertices(); i++) {
    float index = (float) (i - 1) / cone->getUnmappedMesh()->getNumVertices();
    
    ofVec3f center = cone->getUnmappedMesh()->getVertex(0);
    ofVec3f edge = cone->getUnmappedMesh()->getVertex(i);
    
    ofVec3f p1(center.getInterpolated(edge, ofClamp(start - index * spiral + offset, 0, 1)));
    ofVec3f p2(center.getInterpolated(edge, ofClamp(end - index * spiral + offset, 0, 1)));
    
    ofDrawLine(p1, p2);
  }
}
