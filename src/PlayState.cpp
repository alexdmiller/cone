//
//  PlayState.cpp
//  myInnocentSketch
//
//  Created by Alex on 12/4/17.
//
//

#include "PlayState.hpp"
#include "ofMain.h"
#include "mapping.hpp"
#include "Pulser.hpp"
#include "Bath.hpp"

PlayState::PlayState(Cone* _cone, ofxIlda::Frame* _ildaFrame): cone(_cone), ildaFrame(_ildaFrame) {
  canvas.allocate(cone->getRadius() * 2, cone->getRadius() * 2);
  canvas.begin();
  ofClear(0, 0, 0);
  canvas.end();
  
  synths.push_back(new Pulser());
  synths.push_back(new Bath());
  
  receiver.setup(12345);
}

void PlayState::setMap(bool map) {
  this->map = map;
}

void PlayState::draw() {
  while (receiver.hasWaitingMessages()) {
    ofxOscMessage message;
    receiver.getNextMessage(&message);

    for (auto synth : synths) {
      synth->onOscMessage(&message);
    }
  }
  
  ofBackground(0, 0, 0);
  ildaFrame->clear();

  if (map) {
    canvas.begin();
    ofBackground(0, 0, 0);
    drawSynths();
    canvas.end();
    
    canvas.getTexture().bind();
    cone->getProjectedMesh()->draw();
    canvas.getTexture().unbind();
    
    // Map laser points triangle to triangle
    for (auto it = ildaFrame->getPolys().begin(); it != ildaFrame->getPolys().end(); it++) {
      auto vertices = &it->getVertices();
      for (auto v = vertices->begin(); v != vertices->end(); v++) {
        ofMesh* unmapped = cone->getUnmappedMesh();
        ofMesh* mapped = cone->getLaserMesh();
        
        // figure out what triangle the point falls in (in unmapped space)
        int triangleIndex = getContainingTriangle(unmapped, *v);
        
        if (triangleIndex == -1) {
          triangleIndex = getClosestTriangle(unmapped, *v);
        }
        
        // find mapping to point in mapped space
        if (triangleIndex >= 0) {
          ofPoint unmappedTriangle[3] = {
            unmapped->getVertex(unmapped->getIndex(0)),
            unmapped->getVertex(unmapped->getIndex(triangleIndex)),
            unmapped->getVertex(unmapped->getIndex(triangleIndex + 1))};
          
          ofPoint mappedTriangle[3] = {
            mapped->getVertex(mapped->getIndex(0)),
            mapped->getVertex(mapped->getIndex(triangleIndex)),
            mapped->getVertex(mapped->getIndex(triangleIndex + 1))};
          
          ofPoint mappedPoint = triangleToTriangle(unmappedTriangle, mappedTriangle, *v);
          v->set(mappedPoint);
        } else {
          v->set(v->x / ofGetWidth(), v->y / ofGetHeight());
          cout << "WARNING: Point not in triangle\n";
        }
      }
    }

    ildaFrame->update();
  } else {
    ofBackground(0, 0, 0);
    drawSynths();
    
    for (auto it = ildaFrame->getPolys().begin(); it != ildaFrame->getPolys().end(); it++) {
      auto vertices = &it->getVertices();
      for (auto v = vertices->begin(); v != vertices->end(); v++) {
        v->set(v->x / ofGetWidth(), v->y / ofGetHeight());
      }
    }
    ildaFrame->update();
  }
}

void PlayState::drawSynths() {
  for (auto synth : synths) {
    synth->draw(cone, ildaFrame);
  }
}