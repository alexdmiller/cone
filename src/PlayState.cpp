#include "PlayState.hpp"
#include "ofMain.h"
#include "mapping.hpp"

PlayState::PlayState(
                     vector<GeneratorChannel> & _channels,
                     bool _map,
                     ofxAudioAnalyzer* _audioAnalyzer):
channels(_channels),
map(_map),
audioAnalyzer(_audioAnalyzer) {
  for (auto channel : channels) {
    channel.unmute();
  }
}

void PlayState::draw() {
  for (auto channel : channels) {
    channel.draw(map);
  }
}

void PlayState::keyPressed(int key) {
  if (key == 'm') {
    map = !map;
  }
}
