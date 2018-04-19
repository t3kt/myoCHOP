//
//  MyoUpdater.cpp
//  MyoCHOP
//
//  Created by tekt on 4/18/18.
//

#include "MyoUpdater.h"

void MyoUpdater::onPair(MyoPtr dev, uint64_t timestamp, myo::FirmwareVersion firmwareVersion) {
  _manager.registerMyo(dev);
}

void MyoUpdater::onUnpair(MyoPtr dev, uint64_t timestamp) {
  _manager.unregisterMyo(dev);
}

void MyoUpdater::onConnect(MyoPtr dev, uint64_t timestamp, myo::FirmwareVersion firmwareVersion) {
  // TODO: ???
}

void MyoUpdater::onDisconnect(MyoPtr dev, uint64_t timestamp) {
  // TODO: ????
}

void MyoUpdater::onArmSync(MyoPtr dev, uint64_t timestamp, myo::Arm arm, myo::XDirection xDirection) {
  auto& data = _manager[dev].data;
  data.arm = arm;
  data.direction = xDirection;
}

void MyoUpdater::onArmUnsync(MyoPtr dev, uint64_t timestamp) {
  auto& data = _manager[dev].data;
  data.arm = myo::armUnknown;
  data.direction = myo::xDirectionUnknown;
}

void MyoUpdater::onLock(MyoPtr dev, uint64_t timestamp) {
  _manager[dev].data.locked = true;
}

void MyoUpdater::onUnlock(MyoPtr dev, uint64_t timestamp) {
  _manager[dev].data.locked = false;
}

void MyoUpdater::onPose(MyoPtr dev, uint64_t timestamp, myo::Pose pose) {
  _manager[dev].data.setPose(pose);
}

void MyoUpdater::onOrientationData(MyoPtr dev, uint64_t timestamp, const myo::Quaternion<float> &rotation) {
  _manager[dev].data.orient = rotation;
}

void MyoUpdater::onAccelerometerData(MyoPtr dev, uint64_t timestamp, const myo::Vector3<float> &accel) {
  _manager[dev].data.accel = accel;
}

void MyoUpdater::onGyroscopeData(MyoPtr dev, uint64_t timestamp, const myo::Vector3<float> &gyro) {
  _manager[dev].data.gyro = gyro;
}

void MyoUpdater::onRssi(MyoPtr dev, uint64_t timestamp, int8_t rssi) {
  _manager[dev].data.rssi = rssi;
}

void MyoUpdater::onEmgData(MyoPtr dev, uint64_t timestamp, const int8_t *emg) {
  auto& data = _manager[dev].data;
  for (auto i = 0; i < emgLength; i++) {
    data.emg[i] = emg[i];
  }
}
