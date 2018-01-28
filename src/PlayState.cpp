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

PlayState::PlayState(Cone* _cone, ofxIlda::Frame* _ildaFrame, ControllerThread* _controller): cone(_cone), ildaFrame(_ildaFrame), controller(_controller) {
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
    
//    cout << "got message " << message.getAddress() << " " << message.getArgAsFloat(0);
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
        cout << v->x << "," << v->y << "\n";
        v->set(v->x / ofGetWidth(), v->y / ofGetHeight());
        cout << v->x << "," << v->y << "\n\n";
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



/*
void PlayState::drawSynths() {
  t += 0.1;

//  cone->getUnmappedMesh()->clearColors();
//  cone->getUnmappedMesh()->addColor(ofFloatColor((sin(t*t / 50) + 1) / 2));
//  
//  for (int i = 1; i < cone->getUnmappedMesh()->getNumVertices(); i++) {
//    ofVec3f p = cone->getUnmappedMesh()->getVertex(i);
//    cone->getUnmappedMesh()->addColor(ofFloatColor((sin(t*t / 50 + PI / 2) + 1) / 2));
//  }
//  
//  cone->getUnmappedMesh()->draw();
  switch (mode) {
    case 0: {
      float r = t * 100;
      ildaFrame->addPoly().arc(ofPoint(cone->getRadius(), cone->getRadius()), r, r, 0, 360);
      if (r > cone->getRadius()) {
        mode = 1;
        t = 0;
      }
      break;
    }
    case 1: {
      cone->getUnmappedMesh()->clearColors();
      cone->getUnmappedMesh()->addColor(ofFloatColor((sin(t / 2) + 1) / 2));
      
      for (int i = 1; i < cone->getUnmappedMesh()->getNumVertices(); i++) {
        ofVec3f p = cone->getUnmappedMesh()->getVertex(i);
        cone->getUnmappedMesh()->addColor(ofFloatColor((sin(t / 2 + PI / 2) + 1) / 2));
      }
      
      cone->getUnmappedMesh()->draw();
      if (t > 20) {
        mode = 2;
        t = 0;
      }
      break;
    }
    case 2: {
      cone->getUnmappedMesh()->clearColors();
      cone->getUnmappedMesh()->addColor(ofFloatColor(0, 0, (sin(t / 2) + 1) / 2));
      
      for (int i = 1; i < cone->getUnmappedMesh()->getNumVertices(); i++) {
        ofVec3f p = cone->getUnmappedMesh()->getVertex(i);
        cone->getUnmappedMesh()->addColor(ofFloatColor((sin(t / 2 + PI / 2) + 1) / 2, 0, 0));
      }
      
      cone->getUnmappedMesh()->draw();
      if (t > 20) {
        mode = 3;
        t = 0;
      }
      break;
    }
    case 3: {
      int index = ((int) (ofGetElapsedTimef() * 20)) % (cone->getUnmappedMesh()->getNumVertices() - 1) + 1;
      ofDrawTriangle(cone->getUnmappedMesh()->getVertex(0), cone->getUnmappedMesh()->getVertex(index), cone->getUnmappedMesh()->getVertex(index - 1));
      ofxIlda::Poly* p = &ildaFrame->addPoly();
      p->addVertex(cone->getUnmappedMesh()->getVertex(0));
      p->addVertex(cone->getUnmappedMesh()->getVertex(index));
      p->addVertex(cone->getUnmappedMesh()->getVertex(index - 1));
      p->addVertex(cone->getUnmappedMesh()->getVertex(0));
      
      for (int i = 1; i < cone->getUnmappedMesh()->getNumVertices(); i++) {
        ofVec3f p = cone->getUnmappedMesh()->getVertex(i);
        
        float t = (float) (i - 1) / (cone->getUnmappedMesh()->getNumVertices() - 1);
        
        cone->getUnmappedMesh()->addColor(ofFloatColor(pow(ofMap(sin(-t * 2 * PI + ofGetElapsedTimef() * 5), -1, 1, 0, 1), 10)));
      }
      
      if (t > 10) {
        mode = 4;
        t = 0;
      }
      break;
    }
    case 4: {
      float theta = ofRandom(0, PI * 2);
      float r = ofRandom(0, cone->getRadius());
      ildaFrame->addPoly().arc(ofPoint(cone->getRadius() + cos(theta) * r, cone->getRadius() + sin(theta) * r), 5, 5, 0, 360);
      if (t > 5) {
        mode = 5;
        t = 0;
      }
      break;
    }
    case 5: {
      float r = ofRandom(0, cone->getRadius());
      ildaFrame->addPoly().arc(ofPoint(cone->getRadius(), cone->getRadius()), r, r, 0, 360);
      if (t > 5) {
        mode = 6;
        t = 0;
      }
      break;
    }
    case 6: {
      ofxIlda::Poly* p = &ildaFrame->addPoly();
      p->lineTo(ofPoint(0, cone->getRadius()));
      p->lineTo(ofPoint(cone->getRadius() * 2, cone->getRadius()));
      if (t > 5) {
        mode = 7;
        t = 0;
      }
      break;
    }
    case 7: {
      ildaFrame->addPoly().arc(ofPoint(cone->getRadius(), cone->getRadius()), cone->getRadius() / 2, cone->getRadius() / 2, 0, t * 20);
      ildaFrame->addPoly().arc(ofPoint(cone->getRadius(), cone->getRadius()), cone->getRadius() / 3, cone->getRadius() / 3, 0, t * 20);
      
      ofPath path;
      path.arc(ofPoint(cone->getRadius(), cone->getRadius()), cone->getRadius() / 2, cone->getRadius() / 2, 0, t * 20);
      path.draw();
      
      if (t > 20) {
        mode = 8;
        t = 0;
      }
      break;
    }
    case 8: {
        ofxIlda::Poly* p = &ildaFrame->addPoly(ofFloatColor(
                                                            ofMap(sin(ofGetElapsedTimef()), -1, 1, 0.2, 1),
                                                            0,
                                                            ofMap(sin(ofGetElapsedTimef()), -1, 1, 1, 0.2)));
      
        for (float theta = 0; theta <= 2 * PI; theta += 2 * PI / 50) {
          float r = cone->getRadius() / 2 + sin(sin(theta * 5) * theta * 10 + ofGetElapsedTimef() * 10) * 50;
          p->addVertex(
                       cone->getRadius() + cos(theta) * r,
                       cone->getRadius() + sin(theta) * r);
       }
      if (t > 20) {
        mode = 0;
        t = 0;
      }
      break;
    }
  }
}
 */


void PlayState::keyPressed(int key) {
  if (key == 'm') {
    map = !map;
  }
}





// FACE VID STUFF
//
//  for (int i = 0; i < numVids; i++){
//    videoPlayer[i].update();
//  }
//
//  if (videoPlayer[0].getIsMovieDone()) {
//    cout<< "Hasdfasfd\n";
//    for (int i = 0; i < numVids; i++){
//      videoPlayer[i].setFrame(1);
//      videoPlayer[i].play();
//
//    }
//  }
//
//  ofBackground(0);
//
//  for (int i = 0; i < 14; i++) {
//    face[i].begin();
//    ofClear(0);
//    videoPlayer[(i + (int) ofGetElapsedTimef() * 10) % numVids].draw(0, 0, cone->getRadius() * 2, cone->getRadius() * 2);
//    face[i].end();
//
//    mask[i].begin();
//    ofClear(0);
//    ofSetColor(255, 255, 255);
//    ofPushMatrix();
//    ofDrawTriangle(cone->getUnmappedMesh()->getVertex(0), cone->getUnmappedMesh()->getVertex(i + 1), cone->getUnmappedMesh()->getVertex(i + 2));
//    mask[i].end();
//
//    face[i].getTexture().setAlphaMask(mask[i].getTexture());
//    face[i].draw(0, 0);
//  }
//  //mask.draw(0, 0);
//

