#ifndef SoundReactiveGenerator_hpp
#define SoundReactiveGenerator_hpp

#include <stdio.h>
#include "Generator.hpp"
#include "ofxAudioAnalyzer.h"

class SoundReactiveGenerator : public Generator {
public:
  SoundReactiveGenerator(ofxAudioAnalyzer & _audioAnalyzer);
protected:
  void doDraw(Cone* _cone, ofxIlda::Frame* _ildaFrame);
private:
  ofParameter<int> on = 0;
  ofxAudioAnalyzer & audioAnalyzer;
  
  ofColor colors[4] = { ofColor::fromHex(0x0012ff), ofColor::fromHex(0x7e00ff), ofColor::fromHex(0xf058d5), ofColor::fromHex(0xffffff) };
  
  bool thresh = false;
  float r;
  float theta;
//  ofColor color;
};

#endif /* SoundReactiveGenerator_hpp */
