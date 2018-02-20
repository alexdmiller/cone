#include <stdio.h>
#include <string>
#ifndef AppState_hpp
#define AppState_hpp
using namespace std;

class ofApp;

class AppState {

public:
  virtual void draw() {};
  virtual void mouseMoved(float x, float y) {};
  virtual void mouseDragged(float x, float y, int button) {};
  virtual void mousePressed(float x, float y, int button) {};
  virtual void mouseReleased(float x, float y, int button) {};
  virtual void keyPressed(int key) {};
  virtual string getName() {};

private:
};

#endif
