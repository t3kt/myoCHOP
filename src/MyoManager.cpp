//
//  MyoManager.cpp
//  MyoCHOP
//
//  Created by tekt on 4/17/18.
//

#include "MyoManager.h"

MyoId MyoManager::getMyoId(MyoPtr dev) const {
  auto iter = _idsByPointer.find(dev);
  if (iter == _idsByPointer.end()) {
    return invalidMyoId;
  }
  return iter->second;
}

MyoId MyoManager::registerMyo(MyoPtr dev) {
  auto iter = _idsByPointer.find(dev);
  if (iter != _idsByPointer.end()) {
    return iter->second;
  }
  auto id = _nextId++;
  _idsByPointer[dev] = id;
  _deviceIds.push_back(id);
  return id;
}

void MyoManager::unregisterMyo(MyoPtr dev) {
  auto mapIter = _idsByPointer.find(dev);
  if (mapIter != _idsByPointer.end()) {
    _idsByPointer.erase(mapIter);
    auto listIter = std::find(_deviceIds.begin(), _deviceIds.end(), mapIter->second);
    if (listIter != _deviceIds.end()) {
      _deviceIds.erase(listIter);
    }
  }
}
