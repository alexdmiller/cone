//
//  PlayState.hpp
//  myInnocentSketch
//
//  Created by Alex on 12/4/17.
//
//

#ifndef DemoState_hpp
#define DemoState_hpp

#include <stdio.h>
#include "AppState.hpp"
#include "ofMain.h"
#include "Cone.hpp"
#include "ofxOsc.h"
#include "PlayState.hpp"
#include "DemoGenerator.hpp"

#ifndef ether
#define ether
#include "ofxEtherdream.h"
#endif

class DemoState : public AppState {

public:
  DemoState(vector<GeneratorChannel> & _channels,
            bool _map);
  ~DemoState();
  void draw();
  string getName() {
    return "demo";
  }

private:
  vector<GeneratorChannel> & channels;
  bool map;
};

#endif /* PlayState_hpp */
