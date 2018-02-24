#include <stdio.h>
#include "Generator.hpp"
#include "GradientGenerator.hpp"
#include "PulseGenerator.hpp"
#include "ShaderGenerator.hpp"
#include "SoundReactiveGenerator.hpp"

vector<Generator*> createGenerators(ofxAudioAnalyzer & audioAnalyzer) {
  vector<Generator*> generators;
  generators.push_back(new SoundReactiveGenerator(audioAnalyzer));
  generators.push_back(new ShaderGenerator());
  generators.push_back(new PulseGenerator());
  generators.push_back(new GradientGenerator());
  return generators;
}
