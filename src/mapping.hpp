//
//  mapping.hpp
//  myInnocentSketch
//
//  Created by Alex on 11/29/17.
//
//

#ifndef mapping_hpp
#define mapping_hpp

#include <stdio.h>
#include "ofMain.h"

bool pointInTriangle(ofPoint triangle[3], ofPoint p);
ofPoint triangleToReference(ofPoint triangle[3], ofPoint p);
ofPoint referenceToTriangle(ofPoint triangle[3], ofPoint p);
ofPoint triangleToTriangle(ofPoint triangleA[3], ofPoint triangleB[3], ofPoint p);
int getContainingTriangle(ofMesh* mesh, ofPoint p);
int getClosestTriangle(ofMesh* mesh, ofPoint p);

#endif /* mapping_hpp */
