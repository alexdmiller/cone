#include "GeneratorChannel.hpp"
#include "Generator.hpp"
#include "Cone.hpp"
#include "mapping.hpp"

GeneratorChannel::GeneratorChannel(Cone & _cone) : cone(_cone) {
  canvas.allocate(cone.getRadius() * 2, cone.getRadius() * 2);
  canvas.begin();
  ofClear(0, 0, 0);
  canvas.end();
}

void GeneratorChannel::addGenerator(Generator* generator) {
  generators.push_back(generator);
}

void GeneratorChannel::addAllGenerators(vector<Generator*> newGens) {
  for (auto generator : newGens) {
    generators.push_back(generator);
  }
}

void GeneratorChannel::removeGenerator(int index) {
  generators.erase(generators.begin() + index);
}

void GeneratorChannel::clear() {
  generators.clear();
}

void GeneratorChannel::draw(ofxIlda::Frame* ildaFrame, bool map) {
  ofBackground(0, 0, 0);
  ildaFrame->clear();
  
  cout << "map\n";
  
  // If mapping is turned on, both the projected image and the
  // point sent to the laser interface need to be transformed
  // according to the cone's projected mesh.
  if (map) {
    // Draw to the canvas FBO
    canvas.begin();
    
    ofBackground(0, 0, 0);
    
    // Render all the visual synths. Synths can draw to both the
    // projector and the laser.
    renderGenerators(ildaFrame);
    
    canvas.end();
    
    // Draw the canvas as a texture on the cone's projected mesh
    // This warps the image so it projection maps the cone
    canvas.getTexture().bind();
    cone.getProjectedMesh()->draw();
    canvas.getTexture().unbind();
    
    // Transform the points sent to the laser from unprojected space
    // to projected space
    for (auto it = ildaFrame->getPolys().begin(); it != ildaFrame->getPolys().end(); it++) {
      auto vertices = &it->getVertices();
      for (auto v = vertices->begin(); v != vertices->end(); v++) {
        ofMesh* unmapped = cone.getUnmappedMesh();
        ofMesh* mapped = cone.getLaserMesh();
        
        // figure out what triangle the point falls in (in unmapped space)
        int triangleIndex = getContainingTriangle(unmapped, *v);
        
        if (triangleIndex == -1) {
          triangleIndex = getClosestTriangle(unmapped, *v);
        }
        
        // find mapping to point in mapped space
        if (triangleIndex >= 0) {
          ofPoint unmappedTriangle[3] = {
            unmapped->getVertex(unmapped->getIndex(0)),
            unmapped->getVertex(unmapped->getIndex(triangleIndex)),
            unmapped->getVertex(unmapped->getIndex(triangleIndex + 1))};
          
          ofPoint mappedTriangle[3] = {
            mapped->getVertex(mapped->getIndex(0)),
            mapped->getVertex(mapped->getIndex(triangleIndex)),
            mapped->getVertex(mapped->getIndex(triangleIndex + 1))};
          
          ofPoint mappedPoint = triangleToTriangle(unmappedTriangle, mappedTriangle, *v);
          v->set(mappedPoint);
        } else {
          v->set(v->x / ofGetWidth(), v->y / ofGetHeight());
          cout << "WARNING: Point not in triangle\n";
        }
      }
    }

  } else {
    ofBackground(0, 0, 0);
    renderGenerators(ildaFrame);
    
    cout << "gen channel: " << ildaFrame->getPolys().size() << "\n";
    
    for (auto it = ildaFrame->getPolys().begin(); it != ildaFrame->getPolys().end(); it++) {
      auto vertices = &it->getVertices();
      for (auto v = vertices->begin(); v != vertices->end(); v++) {
        v->set(v->x / ofGetWidth(), v->y / ofGetHeight());
      }
    }
  }
}

void GeneratorChannel::renderGenerators(ofxIlda::Frame* ildaFrame) {
  for (auto generator : generators) {
    generator->draw(&cone, ildaFrame);
  }
}

int GeneratorChannel::numGenerators() {
  return generators.size();
}

Generator* GeneratorChannel::getGenerator(int index) {
  return generators.at(index);
}

vector<Generator*>& GeneratorChannel::getGenerators() {
  return generators;
}

Cone* GeneratorChannel::getCone() {
  return &cone;
}

void GeneratorChannel::mute() {
  for (auto generator : generators) {
    generator->mute();
  }
}

void GeneratorChannel::unmute() {
  for (auto generator : generators) {
    generator->unmute();
  }
}

void GeneratorChannel::unmute(int index) {
  generators.at(index)->unmute();
}

