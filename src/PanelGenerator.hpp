//
//  PanelGenerator.hpp
//  cone
//
//  Created by Alex on 2/28/18.
//
//

#ifndef PanelGenerator_hpp
#define PanelGenerator_hpp

#include <stdio.h>
#include "Generator.hpp"

class PanelGenerator : public Generator {
public:
  PanelGenerator();
  void onTrigger(bool & value);

protected:
  void doDraw(Cone* _cone, ofxIlda::Frame* _ildaFrame);
  
private:
  ofParameter<int> panelIndex = 0;
  ofParameter<ofColor> color = ofColor(255, 255, 255, 0);
  ofParameter<bool> trigger = false;
  ofParameter<float> decay = 0.1;

  ofColor colors[4] = { ofColor::fromHex(0x0012ff), ofColor::fromHex(0x7e00ff), ofColor::fromHex(0xf058d5), ofColor::fromHex(0xffffff) };
  
  struct Flash {
    ofColor color;
    int index;
    bool outline;
  };

  vector<Flash> flashes;
};

#endif /* PanelGenerator_hpp */
