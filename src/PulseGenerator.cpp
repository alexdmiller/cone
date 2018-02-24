#include "PulseGenerator.hpp"

PulseGenerator::PulseGenerator() : Generator("pulse") {
  addParameter(pulseSpeed.set("speed", 5, 0, 10));
  addParameter(color.set("color", ofColor(100), ofColor(0), ofColor(255)));
  addParameter(pulse.set("pulse", "pulse"));

  pulse.addListener(this, &PulseGenerator::onPulse);
};

void PulseGenerator::onPulse(bool & value) {
  pulses.push_back(0);
}

void PulseGenerator::doDraw(Cone* cone, ofxIlda::Frame* ildaFrame) {
  ildaFrame->params.output.color = ofFloatColor(color.get());
  for (int i = pulses.size() - 1; i >= 0; i--) {
    if (pulses[i] > cone->getRadius()) {
      pulses.erase(pulses.begin() + i);
    } else {
      pulses[i] += pulseSpeed;
      ildaFrame->addPoly().arc(ofPoint(cone->getRadius(), cone->getRadius()), pulses[i], pulses[i], 0, 360);
    }
  }
}

