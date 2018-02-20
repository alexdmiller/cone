#include "ofApp.h"
#include "LaserEditState.hpp"
#include "ProjectorEditState.hpp"
#include "PlayState.hpp"
#include "DemoState.hpp"
#include "Cone.hpp"
#include "SoundReactiveGenerator.hpp"
#include "ShaderGenerator.hpp"
#include "PulseGenerator.hpp"
#include "GradientGenerator.hpp"
#include "GeneratorTestBedState.hpp"

#define CONE_FILE "cone_data.csv"
#define CODE_RADIUS 700

void ofApp::setup() {
  soundStream.printDeviceList();
  soundStream.setDeviceID(2);
  
  sampleRate = 44100;
  bufferSize = 256;
  channels = 2;
  
  soundStream.setup(this, 0, channels, sampleRate, bufferSize, 4);
  audioAnalyzer.setup(sampleRate, bufferSize, channels);

  etherdream.setup();
  etherdream.setPPS(30000);
  
  ofToggleFullscreen();
  
  
  generators.push_back(new SoundReactiveGenerator(&audioAnalyzer));
  generators.push_back(new ShaderGenerator());
  generators.push_back(new PulseGenerator());
  generators.push_back(new GradientGenerator());
    
  if (ofFile::doesFileExist(CONE_FILE)) {
    cone = Cone::fromFile(CONE_FILE);
  } else {
    cone = Cone::createCone(CODE_RADIUS);
  }
  
  state = new GeneratorTestBedState(cone, &generators, &ildaFrame, etherdream.stateIsFound(), &audioAnalyzer);
}

void ofApp::audioIn(ofSoundBuffer &buffer) {
  audioAnalyzer.analyze(buffer);
}

void ofApp::draw() {
  if (state != nil) {
    state->draw();
    ofDrawBitmapString("current state: " + state->getName(), 10, ofGetHeight() - 30);
    ofDrawBitmapString("T: test bed / [SPACE]: run / P: projector calibration / L: laser calibration / D: demo", 10, ofGetHeight() - 10);
  }
  
  if (etherdream.stateIsFound()) {
    etherdream.setPoints(ildaFrame);
  } else {
    ildaFrame.params.output.color = ofFloatColor(1, 0, 1);
    ildaFrame.draw();
  }
}

void ofApp::keyPressed(int key) {
  if (key == 't') {
    delete state;
    state = new GeneratorTestBedState(cone, &generators, &ildaFrame, etherdream.stateIsFound(), &audioAnalyzer);
  }
  
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
    state = new PlayState(cone, &generators, &ildaFrame, etherdream.stateIsFound(), &audioAnalyzer);
  }
  
  if (key == 'd') {
    delete state;
    state = new DemoState(cone, &ildaFrame, etherdream.stateIsFound(), &audioAnalyzer);
  }
  
  if (state != nil) {
    state->keyPressed(key);
  }
}

void ofApp::mouseDragged(int x, int y, int button) {
  if (state != nil) {
    state->mouseDragged((float) x, (float) y, button);
  }
}

void ofApp::mousePressed(int x, int y, int button) {
  if (state != nil) {
    state->mousePressed((float) x, (float) y, button);
  }
}

void ofApp::mouseReleased(int x, int y, int button){
  if (state != nil) {
    state->mouseReleased((float) x, (float) y, button);
  }
}


void ofApp::exit() {
  cone->save(CONE_FILE);
}

