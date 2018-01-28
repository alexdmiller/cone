#include "testMapping.hpp"
#include "mapping.hpp"

void testMapping::setup() {
  triangleA[0] = ofPoint(100, 100);
  triangleA[1] = ofPoint(400, 100);
  triangleA[2] = ofPoint(300, 300);
  
  triangleB[0] = ofPoint(500, 100);
  triangleB[1] = ofPoint(400, 200);
  triangleB[2] = ofPoint(600, 400);
}

void testMapping::draw() {
  ofBackground(0);
  ofPoint m = ofPoint(ofGetMouseX(), ofGetMouseY());
  ofPoint transformed = triangleToTriangle(triangleA, triangleB, m);
  ofNoFill();
  ofSetLineWidth(2);
  
  ofDrawTriangle(triangleA[0], triangleA[1], triangleA[2]);
  ofDrawTriangle(triangleB[0], triangleB[1], triangleB[2]);
  
  ofDrawCircle(transformed.x, transformed.y, 10);
}