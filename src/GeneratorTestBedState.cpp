#include "GeneratorTestBedState.hpp"
#include "generator_utils.h"

GeneratorTestBedState::GeneratorTestBedState(
                                             GeneratorChannel & _channel,
                                             ofxIlda::Frame* _ildaFrame,
                                             bool _map,
                                             ofxAudioAnalyzer & _audioAnalyzer):
channel(_channel), ildaFrame(_ildaFrame), map(_map), audioAnalyzer(_audioAnalyzer) {
  generatorList.setup();
  generatorList.setName("generators");
  
  for (int i = 0; i < channel.getGenerators().size(); i++) {
    ofxLabel* label = new ofxLabel();
    generatorList.add(label->setup(channel.getGenerators().at(i)->getName()));
    labels.push_back(label);
  }
  
  generatorPanel.setup();
  generatorPanel.setPosition(channel.getCone()->getRadius() * 2, 20);
  generatorPanel.add(&generatorList);
  
  parameterPanel.setup();
  parameterPanel.setPosition(channel.getCone()->getRadius() * 2 + 200, 20);

  selectGenerator(0);
}

GeneratorTestBedState::~GeneratorTestBedState() {
  generatorPanel.unregisterMouseEvents();
  generatorList.unregisterMouseEvents();
  parameterPanel.unregisterMouseEvents();

  for (auto label : labels) {
    delete label;
  }
}

void GeneratorTestBedState::draw() {
  channel.draw(ildaFrame, map);
  generatorPanel.draw();
  parameterPanel.draw();
}

void GeneratorTestBedState::keyPressed(int key) {
  if (key == 359) {
    selectGenerator((selectedGenerator + 1) % channel.numGenerators());
  }
}

void GeneratorTestBedState::selectGenerator(int index) {
  channel.mute();
  parameterPanel.clear();

  selectedGenerator = index;
  channel.unmute(selectedGenerator);

  for (auto label : labels) {
    label->setBackgroundColor(ofFloatColor(0));
  }
  
  parameterPanel.add(*channel.getGenerator(selectedGenerator)->getParameters());
  generatorList.getControl(index)->setBackgroundColor(ofFloatColor(0.5));
}
