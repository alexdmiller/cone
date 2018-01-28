#include "PulseGenerator.hpp"

void PulseGenerator::draw(Cone* cone, ofxIlda::Frame* ildaFrame) {
//  ildaFrame->params.output.color = color;
  for (int i = pulses.size() - 1; i >= 0; i--) {
    if (pulses[i] > cone->getRadius()) {
      pulses.erase(pulses.begin() + i);
    } else {
      pulses[i] += pulseSpeed;
      ildaFrame->addPoly().arc(ofPoint(cone->getRadius(), cone->getRadius()), pulses[i], pulses[i], 0, 360);
    }
  }
}

void PulseGenerator::onOscMessage(ofxOscMessage* message) {
  if (message->getAddress() == "/pulse/new") {
    pulses.push_back(0);
  } else if (message->getAddress() == "/pulse/speed") {
    pulseSpeed = message->getArgAsFloat(0);
  } else if (message->getAddress() == "/pulse/color") {
    color = ofColor::fromHex(message->getArgAsRgbaColor(0));
  }
}
