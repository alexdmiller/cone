#ifndef Cone_hpp
#define Cone_hpp

#include <stdio.h>
#include "ofMain.h"

class Cone {
  
public:
  static Cone* createCone(float radius);
  static Cone* fromFile(string filename);
  
  ofMesh* getUnmappedMesh();
  ofMesh* getProjectedMesh();
  ofMesh* getLaserMesh();
  float getRadius();
  void save(string filename);

private:
  float radius;
  ofMesh unmappedMesh;
  ofMesh projectedMesh;
  ofMesh laserMesh;

  void saveMesh(ofFile* meshFile, ofMesh* mesh);
  void load();
  void loadMesh(string* line, ofMesh* mesh);
  void finishMeshes();
};


#endif /* Cone_hpp */
