#include "SoundReactiveGenerator.hpp"

SoundReactiveGenerator::SoundReactiveGenerator(ofxAudioAnalyzer* _audioAnalyzer) : Generator("sound reactive"),
  audioAnalyzer(_audioAnalyzer) {
  
}

void SoundReactiveGenerator::draw(Cone* cone, ofxIlda::Frame* ildaFrame) {
  float r = audioAnalyzer->getValue(RMS, 0, 0.2);
  
  cone->getUnmappedMesh()->clearColors();
  cone->getUnmappedMesh()->addColor(ofFloatColor(1,1,1, pow(r, 2)));
  
  for (int i = 1; i < cone->getUnmappedMesh()->getNumVertices(); i++) {
    ofVec3f p = cone->getUnmappedMesh()->getVertex(i);
    cone->getUnmappedMesh()->addColor(ofFloatColor(1,1,1,0));
  }
  
  cone->getUnmappedMesh()->draw();
}
