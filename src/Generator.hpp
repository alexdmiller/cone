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
  
  ofParameterGroup* getParameters() {
    return &parameters;
  }
  
  void addParameter(ofAbstractParameter & param) {
    parameters.add(param);
  }
  
  void mute() {
    muted = true;
  }
  
  void unmute() {
    muted = false;
  }
  
  void draw(Cone* cone, ofxIlda::Frame* ildaFrame) {
    if (!muted) {
      doDraw(cone, ildaFrame);
    }
  }
  
  void setChannelIndex(int _channelIndex) {
    channelIndex = _channelIndex;
  }
  
  int getChannelIndex() {
    return channelIndex;
  }
  
protected:
  virtual void doDraw(Cone* _cone, ofxIlda::Frame* _ildaFrame) {};
  
private:
  string name;
  ofParameterGroup parameters;
  bool muted;
  int channelIndex = 0;
};

#endif /* VizSynth_h */
