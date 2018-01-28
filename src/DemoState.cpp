#include "DemoState.hpp"
#include "ofMain.h"

void DemoState::drawSynths() {
  t += 0.1;

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
