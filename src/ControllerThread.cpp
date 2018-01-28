#include "ControllerThread.hpp"

int ControllerThread::getKnob(int knob) {
  return knobs[knob];
}

void ControllerThread::threadedFunction() {
  serial.listDevices();
  serial.setup("tty.usbmodem1679111", 9000);
  
  while (isThreadRunning()) {
    if (serial.available() > 0) {
      unsigned char bytes[8];
      serial.readBytes(bytes, serial.available());
      for (int i = 1; i < 8; i++) {
        knobs[i - 1] = bytes[i];
      }
    }
    
    sleep(50);
  }
}