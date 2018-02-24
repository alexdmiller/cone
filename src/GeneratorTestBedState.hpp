#ifndef GeneratorTestBedState_hpp
#define GeneratorTestBedState_hpp

#include <stdio.h>
#include "ofMain.h"
#include "AppState.hpp"
#include "Generator.hpp"
#include "ofxAudioAnalyzer.h"
#include "Cone.hpp"
#include "ofxGui.h"
#include "GeneratorChannel.hpp"

#ifndef ether
#define ether
#include "ofxEtherdream.h"
#endif

class GeneratorTestBedState : public AppState {
public:
  GeneratorTestBedState(
            GeneratorChannel & _channel,
            ofxIlda::Frame* _ildaFrame,
            bool _map,
            ofxAudioAnalyzer & audioAnalyzer);
  ~GeneratorTestBedState();
  void draw();
  void keyPressed(int key);
  string getName() {
    return "test bed";
  }

private:
  void selectGenerator(int index);

  bool map;
  ofxAudioAnalyzer & audioAnalyzer;
  ofxIlda::Frame* ildaFrame;
  
  GeneratorChannel & channel;
  int selectedGenerator;
  ofxPanel generatorPanel;
  ofxPanel parameterPanel;
  ofxGuiGroup generatorList;
  vector<ofxLabel*> labels;
};

#endif /* GeneratorTestBedState_hpp */
