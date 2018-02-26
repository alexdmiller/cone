#ifndef GeneratorChannel_hpp
#define GeneratorChannel_hpp

#include "Cone.hpp"
#include "Generator.hpp"
#include <stdio.h>

class GeneratorChannel {
public:
  GeneratorChannel(int _channelIndex, Cone & _cone);
  void addGenerator(Generator* generator);
  void addAllGenerators(vector<Generator*> generators);
  void removeGenerator(int index);
  int numGenerators();
  Generator* getGenerator(int index);
  vector<Generator*>& getGenerators();
  void clear();
  void draw(bool map);
  Cone* getCone();
  int getIndex();
  void setUnmappedPosition(float x, float y);
  ofxIlda::Frame & getIldaFrame();
  
  void mute();
  void unmute();
  void unmute(int index);
  
private:
  void renderGenerators();
  
  ofxIlda::Frame ildaFrame;
  ofPoint unmappedPosition;
  ofFbo canvas;
  Cone & cone;
  vector<Generator*> generators;
  int channelIndex = 0;
};

#endif /* GeneratorChannel_hpp */
