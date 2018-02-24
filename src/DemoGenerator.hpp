#ifndef DemoGenerator_hpp
#define DemoGenerator_hpp

#include <stdio.h>

#include <stdio.h>
#include "Generator.hpp"

class DemoGenerator : public Generator {
public:
  DemoGenerator();
protected:
  void doDraw(Cone* _cone, ofxIlda::Frame* _ildaFrame);
private:
  int mode = 0;
  float t = 0;
};


#endif /* DemoGenerator_hpp */
