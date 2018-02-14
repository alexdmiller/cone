#ifndef PlayState_hpp
#define PlayState_hpp

#include <stdio.h>
#include "AppState.hpp"
#include "ofMain.h"
#include "Cone.hpp"
#include "Generator.hpp"
#include "ofxOsc.h"
#include "ofxAudioAnalyzer.h"

#ifndef ether
#define ether
#include "ofxEtherdream.h"
#endif

class PlayState : public AppState {

public:
  PlayState(
            Cone* _cone,
            ofxIlda::Frame* _ildaFrame,
            bool _map,
            ofxAudioAnalyzer* audioAnalyzer);
  void draw();
  void keyPressed(int key);
  
protected:
  virtual void drawSynths();

  ofFbo canvas;
  ofxIlda::Frame* ildaFrame;
  Cone* cone;
  
private:
  vector<Generator*> generators;
  ofxOscReceiver receiver;
  ofxAudioAnalyzer* audioAnalyzer;
  bool map = true;
};

#endif /* PlayState_hpp */
