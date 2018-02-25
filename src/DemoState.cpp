#include "DemoState.hpp"
#include "ofMain.h"

DemoState::DemoState(GeneratorChannel & _channel,
                     ofxIlda::Frame* _ildaFrame,
                     bool _map) : channel(_channel), ildaFrame(_ildaFrame), map(_map) {
  channel.mute();
  channel.addGenerator(&demoGenerator);
};

DemoState::~DemoState() {
  channel.removeGenerator(channel.numGenerators() - 1);
}

void DemoState::draw() {
  channel.draw(ildaFrame, map);
}
