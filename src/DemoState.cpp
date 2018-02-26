#include "DemoState.hpp"
#include "ofMain.h"

DemoState::DemoState(vector<GeneratorChannel> & _channels,
                     bool _map) : channels(_channels), map(_map) {
  for (auto & channel : channels) {
    channel.mute();
    channel.addGenerator(new DemoGenerator());
  }
};

DemoState::~DemoState() {
  for (auto & channel : channels) {
    channel.removeGenerator(channel.numGenerators() - 1);
  }
}

void DemoState::draw() {
  for (auto & channel : channels) {
    channel.draw(map);
  }
}
