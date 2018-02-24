#ifndef GeneratorChannel_hpp
#define GeneratorChannel_hpp

#include "Cone.hpp"
#include "Generator.hpp"
#include <stdio.h>

class GeneratorChannel {
public:
  GeneratorChannel(Cone & _cone);
  void addGenerator(Generator* generator);
  void addAllGenerators(vector<Generator*> generators);
  int numGenerators();
  Generator* getGenerator(int index);
  vector<Generator*>& getGenerators();
  void clear();
  void draw(ofxIlda::Frame* ildaFrame, bool map);
  Cone* getCone();
  
  void mute();
  void unmute();
  void unmute(int index);
  
  
private:
  void renderGenerators(ofxIlda::Frame* ildaFrame);
  
  ofFbo canvas;
  Cone & cone;
  vector<Generator*> generators;
};

#endif /* GeneratorChannel_hpp */
