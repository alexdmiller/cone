#include "ofApp.h"
#include "LaserEditState.hpp"
#include "ProjectorEditState.hpp"
#include "PlayState.hpp"
#include "Cone.hpp"

#define CONE_FILE "cone_data.csv"
#define CODE_RADIUS 400

void ofApp::setup() {
  etherdream.setup();
  etherdream.setPPS(30000);
  
  ofToggleFullscreen();
  
  if (ofFile::doesFileExist(CONE_FILE)) {
    cone = Cone::fromFile(CONE_FILE);
  } else {
    cone = Cone::createCone(CODE_RADIUS);
  }
  
  state = new PlayState(cone, &ildaFrame, &controller);
    
//  controller.startThread(true);
}

ControllerThread* ofApp::getController() {
  return &controller;
}

void ofApp::draw() {  
  state->draw();
  
  if (etherdream.stateIsFound()) {
    etherdream.setPoints(ildaFrame);
  } else {
    ildaFrame.params.output.color = ofFloatColor(1, 0, 1);
    ildaFrame.draw();
  }
}

void ofApp::keyPressed(int key){
  if (key == 'p') {
    delete state;
    state = new ProjectorEditState(cone->getProjectedMesh());
  }
  
  if (key == 'l') {
    delete state;
    state = new LaserEditState(cone->getLaserMesh(), &ildaFrame);
  }
  
  if (key == ' ') {
    delete state;
    state = new PlayState(cone, &ildaFrame, &controller);
  }
    
  state->keyPressed(key);
}

void ofApp::mouseDragged(int x, int y, int button) {
  state->mouseDragged((float) x, (float) y, button);
}

void ofApp::mousePressed(int x, int y, int button) {
  state->mousePressed((float) x, (float) y, button);
}

void ofApp::mouseReleased(int x, int y, int button){
  state->mouseReleased((float) x, (float) y, button);
}

void ofApp::exit() {
  cone->save(CONE_FILE);
}

