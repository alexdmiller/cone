#include "PlayState.hpp"
#include "ofMain.h"
#include "mapping.hpp"

PlayState::PlayState(
                     GeneratorChannel & _channel,
                     ofxIlda::Frame* _ildaFrame,
                     bool _map,
                     ofxAudioAnalyzer* _audioAnalyzer):
channel(_channel),
ildaFrame(_ildaFrame),
map(_map),
audioAnalyzer(_audioAnalyzer) {
  channel.unmute();
}

void PlayState::draw() {
  channel.draw(ildaFrame, map);
}

void PlayState::keyPressed(int key) {
  if (key == 'm') {
    map = !map;
  }
}
