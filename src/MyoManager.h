//
//  MyoManager.hpp
//  MyoCHOP
//
//  Created by tekt on 4/17/18.
//

#pragma once

#include <unordered_map>
#include <vector>
#include "Common.h"

using MyoPtr = myo::Myo*;

class MyoManager {
public:
  MyoManager() : _nextId(0) {}

  MyoId getMyoId(MyoPtr dev) const;
  MyoId registerMyo(MyoPtr dev);
  void unregisterMyo(MyoPtr dev);

  std::size_t count() const { return _deviceIds.size(); }
private:
  std::vector<MyoId> _deviceIds;
  std::unordered_map<MyoPtr, MyoId> _idsByPointer;
  MyoId _nextId;
};
