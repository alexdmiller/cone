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
  ofxAudioAnalyzer & audioAnalyzer;
};

#endif /* SoundReactiveGenerator_hpp */
