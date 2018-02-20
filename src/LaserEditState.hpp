//
//  laserEditState.hpp
//  myInnocentSketch
//
//  Created by Alex on 12/2/17.
//
//

#ifndef laserEditState_hpp
#define laserEditState_hpp

#include <stdio.h>
#include "ofMain.h"
#include "EditMeshState.hpp"

#ifndef ether
#define ether
#include "ofxEtherdream.h"
#endif

class LaserEditState : public EditMeshState {
  
public:
  LaserEditState(ofMesh* _mesh, ofxIlda::Frame* _ildaFrame);
  void draw();
  void mouseDragged(float x, float y, int button);
  void mousePressed(float x, float y, int button);
  void keyPressed(int key);
  
  string getName() {
    return "laser calibration";
  }

private:
  ofxIlda::Frame* ildaFrame;
  ofxIlda::Poly* mousePoly;
  
  int visibleIndex = 0;
};

#endif /* laserEditState_hpp */
