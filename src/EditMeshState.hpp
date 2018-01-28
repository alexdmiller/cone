#ifndef editMeshState_hpp
#define editMeshState_hpp

#include <stdio.h>
#include "AppState.hpp"
#include "ofMain.h"

#ifndef ether
#define ether
#include "ofxEtherdream.h"
#endif

class EditMeshState : public AppState {

public:
  EditMeshState(ofMesh* _mesh): mesh(_mesh) {}
  void mouseDragged(float x, float y, int button);
  void mousePressed(float x, float y, int button);
  void mouseReleased(float x, float y, int button);
  
protected:
  void mousePressed(float x, float y, int button, float radius);

  ofMesh* mesh;
  int selectedIndex = 0;
};

#endif /* editMeshState_hpp */
