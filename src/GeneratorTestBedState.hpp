#ifndef GeneratorTestBedState_hpp
#define GeneratorTestBedState_hpp

#include <stdio.h>
#include "ofMain.h"
#include "AppState.hpp"
#include "Generator.hpp"
#include "ofxAudioAnalyzer.h"
#include "Cone.hpp"
#include "ofxGui.h"
#include "PlayState.hpp"

#ifndef ether
#define ether
#include "ofxEtherdream.h"
#endif

class GeneratorTestBedState : public PlayState {
public:
  GeneratorTestBedState(
            Cone* _cone,
            vector<Generator*>* generators,
            ofxIlda::Frame* _ildaFrame,
            bool _map,
            ofxAudioAnalyzer* audioAnalyzer);
  void draw();
  void keyPressed(int key);
  void drawSynths();
  string getName() {
    return "test bed";
  }

private:
  int selectedGenerator;
  
  // gui
  ofxPanel generatorPanel;
  ofxGuiGroup generatorList;
  ofxPanel parameterPanel;

  vector<ofxLabel*> labels;
  
  void selectGenerator(int index);
};

#endif /* GeneratorTestBedState_hpp */
