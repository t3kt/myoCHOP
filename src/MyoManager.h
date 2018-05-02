//
//  MyoManager.h
//  MyoCHOP
//
//  Created by tekt on 4/17/18.
//

#pragma once

#include <unordered_map>
#include <vector>
#include "Common.h"
#include "MyoData.h"
#include "MyoSettings.h"

class MyoDeviceState {
public:
  MyoDeviceState(MyoPtr device) : _device(device) {}

  MyoData data;

  bool matches(MyoPtr device) const { return device == _device; }
  void applySettings(const MyoSettings& settings);

private:
  MyoPtr _device;
};

class MyoManager {
public:
  MyoDeviceState& registerMyo(MyoPtr dev);
  void unregisterMyo(MyoPtr dev);

  MyoDeviceState& operator[](MyoPtr dev);

  std::size_t count() const { return _devices.size(); }

  bool empty() const { return _devices.empty(); }

  std::vector<MyoDeviceState>& devices() { return _devices; }

  void clear() { _devices.clear(); }
private:
  std::vector<MyoDeviceState> _devices;
};
