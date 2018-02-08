//
//  laserEditState.cpp
//  myInnocentSketch
//
//  Created by Alex on 12/2/17.
//
//

#include "LaserEditState.hpp"

LaserEditState::LaserEditState(ofMesh* _mesh, ofxIlda::Frame* _ildaFrame): EditMeshState(_mesh), ildaFrame(_ildaFrame) {};

void LaserEditState::keyPressed(int key) {
  if (key == 'n') {
    visibleIndex = (visibleIndex + 1) % mesh->getNumVertices();
  }
}

void LaserEditState::mouseDragged(float x, float y, int button) {
  //EditMeshState::mouseDragged(x / ofGetWidth(), y / ofGetHeight(), button);
}

void LaserEditState::mousePressed(float x, float y, int button) {
  //EditMeshState::mousePressed(x / ofGetWidth(), y / ofGetHeight(), button, 0.05);
  
  if (visibleIndex >= 0) {
    mesh->setVertex(visibleIndex, ofPoint(x / ofGetWidth(), y / ofGetHeight(), 0));
  }
}

void LaserEditState::draw() {
  
  ildaFrame->clear();
  
  ildaFrame->addPoly(ofFloatColor(0.5, 0, 0)).arc(mesh->getVertex(visibleIndex), 0.005, 0.005, 0, 360);
  ildaFrame->addPoly(ofFloatColor(0, 0, 0.5)).arc(ofGetMouseX() / (float) ofGetWidth(),
                                                  ofGetMouseY() / (float) ofGetHeight(), 0.005, 0.005, 0, 360);
  ildaFrame->update();
}