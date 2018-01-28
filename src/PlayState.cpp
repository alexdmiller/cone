#include "PlayState.hpp"
#include "ofMain.h"
#include "mapping.hpp"
#include "PulseGenerator.hpp"
#include "GradientGenerator.hpp"

PlayState::PlayState(Cone* _cone, ofxIlda::Frame* _ildaFrame, bool _map): cone(_cone), ildaFrame(_ildaFrame), map(_map) {
  canvas.allocate(cone->getRadius() * 2, cone->getRadius() * 2);
  canvas.begin();
  ofClear(0, 0, 0);
  canvas.end();
  
  generators.push_back(new PulseGenerator());
  generators.push_back(new GradientGenerator());
  
  receiver.setup(12345);
}

void PlayState::draw() {
  while (receiver.hasWaitingMessages()) {
    ofxOscMessage message;
    receiver.getNextMessage(&message);

    for (auto generator : generators) {
      generator->onOscMessage(&message);
    }
  }
  
  ofBackground(0, 0, 0);
  ildaFrame->clear();

  // If mapping is turned on, both the projected image and the
  // point sent to the laser interface need to be transformed
  // according to the cone's projected mesh.
  if (map) {
    // Draw to the canvas FBO
    canvas.begin();
    
    ofBackground(0, 0, 0);
    
    // Render all the visual synths. Synths can draw to both the
    // projector and the laser.
    drawSynths();
    
    canvas.end();
    
    // Draw the canvas as a texture on the cone's projected mesh
    // This warps the image so it projection maps the cone
    canvas.getTexture().bind();
    cone->getProjectedMesh()->draw();
    canvas.getTexture().unbind();
    
    // Transform the points sent to the laser from unprojected space
    // to projected space
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
  for (auto generator : generators) {
    generator->draw(cone, ildaFrame);
  }
}

void PlayState::keyPressed(int key) {
  if (key == 'm') {
    map = !map;
  }
}
