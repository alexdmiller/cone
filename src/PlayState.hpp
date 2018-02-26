#ifndef PlayState_hpp
#define PlayState_hpp

#include <stdio.h>
#include "AppState.hpp"
#include "ofMain.h"
#include "Cone.hpp"
#include "Generator.hpp"
#include "GeneratorChannel.hpp"
#include "ofxOsc.h"
#include "ofxAudioAnalyzer.h"

#ifndef ether
#define ether
#include "ofxEtherdream.h"
#endif

class PlayState : public AppState {

public:
  PlayState(
            vector<GeneratorChannel> & _channels,
            bool _map,
            ofxAudioAnalyzer* audioAnalyzer);
  void draw();
  void keyPressed(int key);
  
  string getName() {
    return "run";
  }
  
protected:
  ofFbo canvas;
  ofxAudioAnalyzer* audioAnalyzer;
  vector<GeneratorChannel> & channels;
private:
  bool map = true;

};

#endif /* PlayState_hpp */
