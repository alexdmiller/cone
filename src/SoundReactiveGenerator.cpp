#include "SoundReactiveGenerator.hpp"

SoundReactiveGenerator::SoundReactiveGenerator(ofxAudioAnalyzer & _audioAnalyzer) : Generator("reactive"),
  audioAnalyzer(_audioAnalyzer) {
    addParameter(on.set("on", 0, 0, 1));
}

void SoundReactiveGenerator::doDraw(Cone* cone, ofxIlda::Frame* ildaFrame) {
  float r = audioAnalyzer.getValue(RMS, getChannelIndex(), 0, true);
  bool isOnset = audioAnalyzer.getOnsetValue(getChannelIndex());
  
  if (on > 0 && r > 0.5) {
    for (int i = 0; i < 5; i++) {
      float theta = ofRandom(0, PI * 2);
      float r = ofRandom(0, cone->getRadius());

      ildaFrame->addPoly(ofFloatColor()).arc(ofPoint(cone->getRadius() + cos(theta) * r, cone->getRadius() + sin(theta) * r), 5, 5, 0, 360);
    }
  }
  
}
