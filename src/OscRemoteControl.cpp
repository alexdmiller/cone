#include "OscRemoteControl.hpp"
#include "utils.h"
#include <string>
#include "ofParameterGroup.h"
#include "ofParameter.h"

void OscRemoteControl::setup(int port) {
  receiver.setup(port);
}

void OscRemoteControl::add(std::string address, ofAbstractParameter * parameter) {
  addressToParameter[address] = parameter;
}

void OscRemoteControl::update() {
  ofxOscMessage message;
  
  while (receiver.hasWaitingMessages()) {
    receiver.getNextMessage(&message);
    std::string address = message.getAddress();
    ofAbstractParameter* parameter = addressToParameter[address];
    if (parameter->type() == typeid(ofParameter<float>).name()) {
      parameter->cast<float>() = message.getArgAsFloat(0);
    }
  }
}
