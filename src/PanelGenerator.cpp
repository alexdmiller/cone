//
//  PanelGenerator.cpp
//  cone
//
//  Created by Alex on 2/28/18.
//
//

#include "PanelGenerator.hpp"

PanelGenerator::PanelGenerator() : Generator("panel") {
  addParameter(panelIndex.set("index", 0, 0, 16));
  addParameter(decay.set("decay", 1, 0, 10));
  addParameter(color.set("color", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
  addParameter(trigger.set("trigger", "trigger"));

  trigger.addListener(this, &PanelGenerator::onTrigger);
};

void PanelGenerator::onTrigger(bool &value) {
  flashes.push_back({ colors[rand() % 4], panelIndex, static_cast<bool>(rand() % 2) });
}

void PanelGenerator::doDraw(Cone* cone, ofxIlda::Frame* ildaFrame) {
  ofMesh* mesh = cone->getUnmappedMesh();
  
  std::vector<Flash>::iterator iter;
  for (iter = flashes.begin(); iter != flashes.end(); ) {
    int i = iter->index % (mesh->getNumVertices() - 1);
    
    ofVec3f v1 = mesh->getVertex(0);
    ofVec3f v2 = mesh->getVertex(i + 1);
    ofVec3f v3 = mesh->getVertex((i + 2) % mesh->getNumVertices());
    
    if (i == mesh->getNumVertices() - 2) {
      v3 = mesh->getVertex(1);
    }
    
    if (iter->color.a >= 0) {
      ofxIlda::Poly* p = &ildaFrame->addPoly(ofFloatColor(
                                                          iter->color.r / 255.0 * iter->color.a / 255.0,
                                                          iter->color.g / 255.0 * iter->color.a / 255.0,
                                                          iter->color.b / 255.0 * iter->color.a / 255.0));
      p->addVertex(v1);
      p->addVertex(v2);
      p->addVertex(v3);
      p->addVertex(v1);
    }
    if (iter->outline) {
      ofSetColor(iter->color);
      ofSetLineWidth(5);
      ofDrawLine(v1, v2);
      ofDrawLine(v1, v3);
    } else {
      ofSetColor(iter->color);
      ofFill();
      
      ofBeginShape();
      ofVertex(v1.x, v1.y);
      ofVertex(v2.x, v2.y);
      ofVertex(v3.x, v3.y);
      ofVertex(v1.x, v1.y);
      ofEndShape();
    }

    iter->color.a -= min((float) iter->color.a, decay.get());
    if (iter->color.a == 0) {
      iter = flashes.erase(iter);
    } else {
      ++iter;
    }

  }
}
