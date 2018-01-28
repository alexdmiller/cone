//
//  mapping.cpp
//  myInnocentSketch
//
//  Created by Alex on 11/29/17.
//
//

#include "mapping.hpp"

bool pointInTriangle(ofPoint triangle[3], ofPoint p) {
  ofPoint reference = triangleToReference(triangle, p);
  return reference.x >= 0 && reference.x <= 1 && reference.y >= 0 && reference.y <= 1 && reference.x + reference.y <= 1;
}

ofPoint triangleToReference(ofPoint triangle[3], ofPoint p) {
  float det = (triangle[0].x - triangle[2].x) * (triangle[1].y - triangle[2].y)
  - (triangle[0].y - triangle[2].y) * (triangle[1].x - triangle[2].x);
  ofPoint diff = p - triangle[2];
  return ofPoint(
     (triangle[1].y - triangle[2].y) / det * diff.x - (triangle[1].x - triangle[2].x) / det * diff.y,
     -(triangle[0].y - triangle[2].y) / det * diff.x + (triangle[0].x - triangle[2].x) / det * diff.y);
}

ofPoint referenceToTriangle(ofPoint triangle[3], ofPoint p) {
  return ofPoint(
     (triangle[0].x - triangle[2].x) * p.x + (triangle[1].x - triangle[2].x) * p.y,
     (triangle[0].y - triangle[2].y) * p.x + (triangle[1].y - triangle[2].y) * p.y)
        + triangle[2];
}

ofPoint triangleToTriangle(ofPoint triangleA[3], ofPoint triangleB[3], ofPoint p) {
  return referenceToTriangle(triangleB, triangleToReference(triangleA, p));
}

int getContainingTriangle(ofMesh* mesh, ofPoint p) {
  for (int i = 1; i < mesh->getNumIndices() - 1; i += 1) {
    ofPoint v1 = mesh->getVertex(mesh->getIndex(0));
    ofPoint v2 = mesh->getVertex(mesh->getIndex(i));
    ofPoint v3 = mesh->getVertex(mesh->getIndex(i + 1));

    ofPoint tri[3] = {v1, v2, v3};
    
    if (pointInTriangle(tri, p)) {
      return i;
    }
  }
  return -1;
}

int getClosestTriangle(ofMesh* mesh, ofPoint p) {
  float closestDistance = 100;
  float closestIndex = -1;
  
  for (int i = 1; i < mesh->getNumIndices() - 1; i += 1) {
    
    
    ofPoint v1 = mesh->getVertex(mesh->getIndex(0));
    ofPoint v2 = mesh->getVertex(mesh->getIndex(i));
    ofPoint v3 = mesh->getVertex(mesh->getIndex(i + 1));
    
    ofPoint tri[3] = {v1, v2, v3};
    ofPoint referencePoint = triangleToReference(tri, p);
    
    if (referencePoint.length() < closestDistance) {
      closestIndex = i;
      closestDistance = referencePoint.length();
    }
  }
  return closestIndex;
}