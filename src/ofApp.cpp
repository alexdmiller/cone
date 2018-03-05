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
#include "PanelGenerator.hpp"
#include "OutlineGenerator.hpp"
#include "WarpLines.hpp"
#include "ofParameter.h"

#define NUM_CONES 2
#define CONE_FILE(n) "cone_" n ".csv"
#define CONE_RADIUS 400


void ofApp::setup() {
  soundStream.printDeviceList();
  soundStream.setDeviceID(3);
  
  sampleRate = 44100;
  bufferSize = 256;
  channels = 2;
  
  
  soundStream.setup(this, 0, channels, sampleRate, bufferSize, 4);
  audioAnalyzer.setup(sampleRate, bufferSize, channels);

  etherdream.setup();
  etherdream.setPPS(30000);
  
  remote.setup(9999);
  
  ofToggleFullscreen();
  
  
  for (int i = 0; i < NUM_CONES; i++) {
    Cone* cone;
    if (ofFile::doesFileExist("cone_" + ofToString(i) + ".csv")) {
      cone = Cone::fromFile("cone_" + ofToString(i) + ".csv");
    } else {
      cone = Cone::createCone(CONE_RADIUS);
    }

    GeneratorChannel channel(i, *cone);
    channel.addGenerator(new WarpLines());
    channel.addGenerator(new OutlineGenerator());
    channel.addGenerator(new PanelGenerator());
    channel.addGenerator(new SoundReactiveGenerator(audioAnalyzer));
    channel.addGenerator(new ShaderGenerator());
    channel.addGenerator(new PulseGenerator());
    channel.addGenerator(new GradientGenerator());
    
    
    channel.setUnmappedPosition(CONE_RADIUS * 2 * i, 0);
    
    for (auto & generator : channel.getGenerators()) {
      ofParameterGroup* group = generator->getParameters();
      for (auto parameter : *group) {
        remote.add("/" + ofToString(i) + "/" + group->getName() + "/" + parameter->getName(), parameter.get());
      }
    }
    
    generatorChannels.push_back(channel);
  }
  
  state = new GeneratorTestBedState(generatorChannels, etherdream.stateIsFound(), audioAnalyzer);
}

void ofApp::audioIn(ofSoundBuffer &buffer) {
  audioAnalyzer.analyze(buffer);
}

void ofApp::draw() {
  remote.update();
  ildaFrame.clear();
  ofBackground(0, 0, 0);
  
  ofSetColor(ofColor(255));

  if (state != nil) {
    state->draw();
    
    if (state->getName() != "run") {
      ofDrawBitmapString("current state: " + state->getName(), 10, ofGetHeight() - 50);
      ofDrawBitmapString("selected cone: " + ofToString(selectedChannel), 10, ofGetHeight() - 30);
      ofDrawBitmapString("T: test bed / [SPACE]: run / P: projector calibration / L: laser calibration / C: next cone / D: demo", 10, ofGetHeight() - 10);
    }
  }
  
  ildaFrame.update();

  etherdream.clear();
  if (etherdream.stateIsFound()) {
    for (auto & channel : generatorChannels) {
      etherdream.addPoints(channel.getIldaFrame());
    }
    etherdream.addPoints(ildaFrame);
  } else {
    for (auto & channel : generatorChannels) {
      channel.getIldaFrame().draw();
    }
    ildaFrame.draw();
  }
  
}

void ofApp::keyPressed(int key) {
  if (key == 't') {
    delete state;
    state = new GeneratorTestBedState(generatorChannels, etherdream.stateIsFound(), audioAnalyzer);
  }
  
  if (key == 'p') {
    delete state;
    state = new ProjectorEditState(generatorChannels.at(selectedChannel).getCone()->getProjectedMesh());
  }
  
  if (key == 'l') {
    delete state;
    state = new LaserEditState(generatorChannels.at(selectedChannel).getCone()->getLaserMesh(), &ildaFrame);
  }
  
  if (key == ' ') {
    delete state;
    state = new PlayState(generatorChannels, etherdream.stateIsFound(), &audioAnalyzer);
  }
  
  if (key == 'd') {
    delete state;
    state = new DemoState(generatorChannels, etherdream.stateIsFound());
  }
  
  if (key == 'c') {
    selectedChannel = (selectedChannel + 1) % generatorChannels.size();
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
  
  for (auto & channel : generatorChannels) {
    channel.getCone()->save("cone_" + ofToString(channel.getIndex()) + ".csv");
  }
}


void ofApp::exit() {
  for (auto & channel : generatorChannels) {
    channel.getCone()->save("cone_" + ofToString(channel.getIndex()) + ".csv");
  }
}

