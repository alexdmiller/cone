#include "EditMeshState.hpp"

void EditMeshState::mouseDragged(float x, float y, int button) {
  if (selectedIndex >= 0) {
    mesh->setVertex(selectedIndex, ofPoint(x, y, 0));
  }
}

void EditMeshState::mousePressed(float x, float y, int button) {
  mousePressed(x, y, button, 10);
}

void EditMeshState::mousePressed(float x, float y, int button, float radius) {
  ofPoint mouse = ofPoint(x, y);
  for (int i = 0; i < mesh->getNumVertices(); i++) {
    ofVec3f p = mesh->getVertex(i);
    
    if (p.distance(mouse) < radius) {
      selectedIndex = i;
      break;
    }
  }
}

void EditMeshState::mouseReleased(float x, float y, int button){
  selectedIndex = -1;
}