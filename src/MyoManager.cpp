//
//  MyoManager.cpp
//  MyoCHOP
//
//  Created by tekt on 4/17/18.
//

#include "MyoManager.h"

void MyoDeviceState::applySettings(const MyoSettings &settings) {
  _device->setStreamEmg(settings.outputEmg
                        ? myo::Myo::streamEmgEnabled : myo::Myo::streamEmgDisabled);
  if (settings.outputRssi) {
    _device->requestRssi();
  }
}

MyoDeviceState& MyoManager::registerMyo(MyoPtr dev) {
  _devices.emplace_back(dev);
  return _devices.back();
}

void MyoManager::unregisterMyo(MyoPtr dev) {
  for (auto iter = _devices.begin();
       iter != _devices.end();
       iter++) {
    if (iter->matches(dev)) {
      _devices.erase(iter);
      return;
    }
  }
}

MyoDeviceState& MyoManager::operator[](MyoPtr dev) {
  for (auto& state : _devices) {
    if (state.matches(dev)) {
      return state;
    }
  }
  return registerMyo(dev);
}
