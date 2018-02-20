#ifndef projectorEditState_hpp
#define projectorEditState_hpp

#include <stdio.h>
#include "ofMain.h"
#include "EditMeshState.hpp"

#ifndef ether
#define ether
#include "ofxEtherdream.h"
#endif

class ProjectorEditState : public EditMeshState {
public:
  ProjectorEditState(ofMesh* _mesh) : EditMeshState(_mesh) {}
  void draw();
  
  std::string getName() {
    return "projector calibration";
  }

};

#endif /* projectorEditState_hpp */
