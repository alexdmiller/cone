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
    if (parameter != nil) {
      if (parameter->type() == typeid(ofParameter<float>).name()) {
        parameter->cast<float>() = message.getArgAsFloat(0);
      } else if (parameter->type() == typeid(ofParameter<bool>).name()) {
        parameter->cast<bool>() = message.getArgAsBool(0);
      } else if (parameter->type() == typeid(ofParameter<int>).name()) {
        parameter->cast<int>() = message.getArgAsInt(0);
      } else if (parameter->type() == typeid(ofParameter<ofColor>).name()) {
        std::int32_t rgba = message.getArgAsRgbaColor(0);
        int red = (rgba & 0xFF000000) >> 24;
        int green = (rgba & 0x00FF0000) >> 16;
        int blue = (rgba & 0x0000FF00) >> 8;
        int alpha = (rgba & 0x000000FF) >> 0;

        parameter->cast<ofColor>() = ofColor(red, green, blue, alpha);
      }
    } else {
      cout << "cannot find parameter for address " << address;
    }
  }
}
