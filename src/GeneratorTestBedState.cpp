#include "GeneratorTestBedState.hpp"

GeneratorTestBedState::GeneratorTestBedState(
                     Cone* _cone,
                     vector<Generator*>* _generators,
                     ofxIlda::Frame* _ildaFrame,
                     bool _map,
                     ofxAudioAnalyzer* _audioAnalyzer): PlayState(_cone, _generators, _ildaFrame, _map, _audioAnalyzer) {

  generatorList.setup();
  generatorList.setName("generators");
  
  for (int i = 0; i < generators->size(); i++) {
    ofxLabel* label = new ofxLabel();
    generatorList.add(label->setup(generators->at(i)->getName()));
    labels.push_back(label);
  }
  
  generatorPanel.setup();
  generatorPanel.setPosition(cone->getRadius() * 2, 20);
  generatorPanel.add(&generatorList);
  
  parameterPanel.setup();
  parameterPanel.setPosition(cone->getRadius() * 2 + 200, 20);

  selectGenerator(0);
}

void GeneratorTestBedState::draw() {
  PlayState::draw();
  generatorPanel.draw();
  parameterPanel.draw();
}

void GeneratorTestBedState::drawSynths() {
  generators->at(selectedGenerator)->draw(cone, ildaFrame);
}

void GeneratorTestBedState::keyPressed(int key) {
  if (key == 359) {
    selectGenerator((selectedGenerator + 1) % generators->size());
  }
}

void GeneratorTestBedState::selectGenerator(int index) {
  parameterPanel.clear();
  
  selectedGenerator = index;
  for (auto label : labels) {
    label->setBackgroundColor(ofFloatColor(0));
  }
  
  parameterPanel.add(generators->at(selectedGenerator)->getParameters());
  
  generatorList.getControl(index)->setBackgroundColor(ofFloatColor(0.5));
}
