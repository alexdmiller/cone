#include "DemoState.hpp"
#include "ofMain.h"

// TODO: create a demo generator that has this code in it
// RULE: all drawing happens in generators

void DemoState::draw() {
  demoGenerator.draw(cone, ildaFrame);
}
