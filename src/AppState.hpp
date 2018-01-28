#include <stdio.h>

#ifndef AppState_hpp
#define AppState_hpp

class ofApp;

class AppState {

public:
  virtual void draw() {};
  virtual void mouseMoved(float x, float y) {};
  virtual void mouseDragged(float x, float y, int button) {};
  virtual void mousePressed(float x, float y, int button) {};
  virtual void mouseReleased(float x, float y, int button) {};
  virtual void keyPressed(int key) {};
};

#endif
