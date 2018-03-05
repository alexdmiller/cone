#include "WarpLines.hpp"

WarpLines::WarpLines() : Generator("warp") {
  addParameter(color.set("color", ofColor(255), ofColor(0, 0, 0, 0), ofColor(255)));
  addParameter(speed.set("speed", 0, -2, 2));
  addParameter(wavelength.set("wavelength", 1, 0.01, 1.5));
  addParameter(gap.set("gap", 0.5, -1, 1));
  addParameter(step.set("step", 0.01, 0.001, 0.1));
  
  addParameter(resetClock.set("reset_clock", "reset_clock"));
  
  resetClock.addListener(this, &WarpLines::reset);
};

void WarpLines::reset(bool & value) {
  time = 0;
}

void WarpLines::doDraw(Cone* cone, ofxIlda::Frame* ildaFrame) {
  ofSetColor(color);
  
  time += speed;
  for (int i = 1; i < cone->getUnmappedMesh()->getNumVertices(); i++) {
    ofVec3f center = cone->getUnmappedMesh()->getVertex(0);
    ofVec3f edge = cone->getUnmappedMesh()->getVertex(i);
    
    for (float t = 0; t <= 1; t += step) {
      float v = cos(t * 100.0 * wavelength + time) + gap;
      if (v > 0) {
        ofVec3f p1(center.getInterpolated(edge, ofClamp(t, 0, 1)));
        ofVec3f p2(center.getInterpolated(edge, ofClamp(t + step, 0, 1)));
        ofDrawLine(p1, p2);
      }
    }
  }
}