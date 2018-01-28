#pragma once

#include "ofMain.h"
#include "AppState.hpp"
#include "Cone.hpp"
#include "ControllerThread.hpp"

#ifndef ether
#define ether
#include "ofxEtherdream.h"
#endif

class ofApp : public ofBaseApp {

public:
  void setup();
  void draw();
  void exit();
  void keyPressed(int key);
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  ControllerThread* getController();

private:
  Cone* cone;
  ofxEtherdream etherdream;
  ofxIlda::Frame ildaFrame;
  AppState* state;
  ControllerThread controller;
};