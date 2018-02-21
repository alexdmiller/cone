#ifndef OscRemoteControl_hpp
#define OscRemoteControl_hpp

#include <stdio.h>
#include <string>
#include "ofParameter.h"
#include "ofxOscReceiver.h"
#include <unordered_map>

class OscRemoteControl {
public:
  void setup(int port);
  void add(std::string address, ofAbstractParameter * parameter);
  void update();
  
private:
  ofxOscReceiver receiver;
  unordered_map<std::string, ofAbstractParameter*> addressToParameter;
};

#endif /* OscRemoteControl_hpp */
