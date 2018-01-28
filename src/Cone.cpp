#include "Cone.hpp"

ofMesh* Cone::getUnmappedMesh() {
  return &unmappedMesh;
}

ofMesh* Cone::getProjectedMesh() {
  return &projectedMesh;
}

ofMesh* Cone::getLaserMesh() {
  return &laserMesh;
}

// Creates all three meshes from scratch
Cone* Cone::createCone(float radius) {
  Cone* cone = new Cone();
  
  cone->radius = radius;
  
  ofPoint center = ofPoint(radius, radius);
  cone->unmappedMesh.addVertex(center);
  
  for (int i = 1; i < 16; i++) {
    cone->unmappedMesh.addVertex(ofPoint(
                                   center.x + cos(i * (2 * PI / 15)) * radius,
                                   center.y + sin(i * (2 * PI / 15)) * radius, 0));
  }
  
  cone->projectedMesh.addVertices(cone->unmappedMesh.getVertices());
  cone->laserMesh.addVertices(cone->unmappedMesh.getVertices());
  
  for (int i = 0; i < cone->laserMesh.getNumVertices(); i++) {
    ofPoint v = cone->laserMesh.getVertex(i);
    cone->laserMesh.setVertex(i, ofPoint(v.x / ofGetWidth() / 2, v.y / ofGetHeight() / 2));
  }
  
  cone->finishMeshes();
  
  return cone;
}

void Cone::finishMeshes() {
  unmappedMesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
  projectedMesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
  laserMesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);

  unmappedMesh.addIndex(0);
  
  for (int i = 1; i < unmappedMesh.getNumVertices(); i++) {
    unmappedMesh.addIndex(i);
  }
  
  // Connect last triangle
  unmappedMesh.addIndex(0);
  unmappedMesh.addIndex(1);
  unmappedMesh.addIndex(unmappedMesh.getNumVertices() - 1);
  
  vector<ofVec2f> copy(unmappedMesh.getVertices().begin(),
                       unmappedMesh.getVertices().end());
  projectedMesh.addTexCoords(copy);
  projectedMesh.addIndices(unmappedMesh.getIndices());
  
  laserMesh.addIndices(unmappedMesh.getIndices());
}

float Cone::getRadius() {
  return radius;
}

void Cone::save(string filename) {
  ofFile file;
  file.open(filename, ofFile::WriteOnly);
  file << radius << "\n";
  saveMesh(&file, &unmappedMesh);
  saveMesh(&file, &projectedMesh);
  saveMesh(&file, &laserMesh);
  file.close();
}

void Cone::saveMesh(ofFile* meshFile, ofMesh* mesh) {
  for (int i = 0; i < mesh->getNumVertices(); i++) {
    (*meshFile) << mesh->getVertex(i).x << "," << mesh->getVertex(i).y << ",";
  }
  (*meshFile) << "\n";
}

Cone* Cone::fromFile(string filename) {
  auto lines = ofSplitString(ofBufferFromFile(filename).getText(), "\n");
  
  Cone* cone = new Cone();
  cone->radius = ofToFloat(lines.at(0));
  cone->loadMesh(&lines.at(1), &cone->unmappedMesh);
  cone->loadMesh(&lines.at(2), &cone->projectedMesh);
  cone->loadMesh(&lines.at(3), &cone->laserMesh);
  
  cone->finishMeshes();
  
  return cone;
}

void Cone::loadMesh(string* line, ofMesh* mesh) {
  mesh->clear();
  
  stringstream ss(*line);
  vector<float> coordinates;
  
  float x, y;
  while (ss.good()) {
    string sub;
    
    getline(ss, sub, ',');
    if (sub != "") {
      x = ofToFloat(sub);
      getline(ss, sub, ',');
      y = ofToFloat(sub);
      mesh->addVertex(ofPoint(x, y));
    }
  }
}

