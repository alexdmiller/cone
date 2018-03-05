#include "GeneratorTestBedState.hpp"
#include "generator_utils.h"



// TODO: individually control cones w sliders



GeneratorTestBedState::GeneratorTestBedState(
                                             vector<GeneratorChannel> & _channels,
                                             bool _map,
                                             ofxAudioAnalyzer & _audioAnalyzer):
channels(_channels), map(_map), audioAnalyzer(_audioAnalyzer) {
  generatorList.setup();
  generatorList.setName("generators");
  
  GeneratorChannel & channel = channels[0];
  
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
  for (auto & channel : channels) {
    channel.draw(map);
  }
  
  generatorPanel.draw();
  parameterPanel.draw();
}

void GeneratorTestBedState::keyPressed(int key) {
  if (key == 359) {
    selectGenerator((selectedGenerator + 1) % channels.at(0).numGenerators());
  }
}

void GeneratorTestBedState::selectGenerator(int index) {
  selectedGenerator = index;

  parameterPanel.clear();

  for (auto & channel : channels) {
    channel.mute();
    channel.unmute(selectedGenerator);
  }

  for (auto label : labels) {
    label->setBackgroundColor(ofFloatColor(0));
  }
  
  parameterPanel.add(*channels.at(0).getGenerator(selectedGenerator)->getParameters());
  generatorList.getControl(index)->setBackgroundColor(ofFloatColor(0.5));
}
