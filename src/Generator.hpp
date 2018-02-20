#ifndef VizSynth_h
#define VizSynth_h

#include <stdio.h>
#include "Cone.hpp"
#include "ofxOsc.h"
#include <array>

#ifndef ether
#define ether
#include "ofxEtherdream.h"
#endif

class Generator {

public:
  Generator(string _name) : name(_name) {
    parameters.setName(_name);
  };
  
  string getName() {
    return name;
  }
  
  ofParameterGroup getParameters() {
    return parameters;
  }
  
  void addParameter(ofAbstractParameter & param) {
    parameters.add(param);
  }
  
  virtual void draw(Cone* _cone, ofxIlda::Frame* _ildaFrame) {};
  virtual void onOscMessage(ofxOscMessage* message) {};
  
private:
  string name;
  ofParameterGroup parameters;
};

#endif /* VizSynth_h */
