#include "ProjectorEditState.hpp"
#include "mapping.hpp"

void ProjectorEditState::draw() {
  ofBackground(0);
  ofSetLineWidth(1);
  mesh->disableColors();
  mesh->draw(OF_MESH_WIREFRAME);
  
  ofSetLineWidth(5);
  ofSetColor(255, 0, 0);
  ofDrawLine(mesh->getVertex(0), mesh->getVertex(1));
}