//
//  MyoUpdater.cpp
//  MyoCHOP
//
//  Created by tekt on 4/18/18.
//

#include "MyoUpdater.h"

void MyoUpdater::onPair(MyoPtr dev, uint64_t timestamp, myo::FirmwareVersion firmwareVersion) {
  _manager.registerMyo(dev);
  _debug.log("onPair") << "t: " << timestamp << ", firmware: " << firmwareVersion << std::endl;
}

void MyoUpdater::onUnpair(MyoPtr dev, uint64_t timestamp) {
  _manager.unregisterMyo(dev);
  _debug.log("onUnpair") << "t: " << timestamp << std::endl;
}

void MyoUpdater::onConnect(MyoPtr dev, uint64_t timestamp, myo::FirmwareVersion firmwareVersion) {
  // TODO: ???
  _debug.log("onConnect") << "t: " << timestamp << ", firmware: " << firmwareVersion << std::endl;
}

void MyoUpdater::onDisconnect(MyoPtr dev, uint64_t timestamp) {
  // TODO: ????
  _debug.log("onDisconnect") << "t: " << timestamp << std::endl;
}

void MyoUpdater::onArmSync(MyoPtr dev, uint64_t timestamp, myo::Arm arm, myo::XDirection xDirection) {
  if (!_settings.outputArm && !_settings.outputDirection) {
    return;
  }
  auto& data = _manager[dev].data;
  data.arm = arm;
  data.direction = xDirection;
  _debug.log("onArmSync") << "t: " << timestamp
    <<  "arm: " << arm << ", dir: " << xDirection << std::endl;
}

void MyoUpdater::onArmUnsync(MyoPtr dev, uint64_t timestamp) {
  if (!_settings.outputArm && !_settings.outputDirection) {
    return;
  }
  auto& data = _manager[dev].data;
  data.arm = myo::armUnknown;
  data.direction = myo::xDirectionUnknown;
  _debug.log("onArmUnsync") << "t: " << timestamp << std::endl;
}

void MyoUpdater::onLock(MyoPtr dev, uint64_t timestamp) {
  _manager[dev].data.locked = true;
  _debug.log("onLock") << "t: " << timestamp << std::endl;
}

void MyoUpdater::onUnlock(MyoPtr dev, uint64_t timestamp) {
  _manager[dev].data.locked = false;
  _debug.log("onUnlock") << "t: " << timestamp << std::endl;
}

void MyoUpdater::onPose(MyoPtr dev, uint64_t timestamp, myo::Pose pose) {
  _manager[dev].data.setPose(pose);
  _debug.log("onPose") << "t: " << timestamp << "pose: " << pose << std::endl;
}

void MyoUpdater::onOrientationData(MyoPtr dev, uint64_t timestamp, const myo::Quaternion<float> &rotation) {
  if (!_settings.outputOrientation && !_settings.outputOrientationQuat) {
    return;
  }
  _manager[dev].data.orient = rotation;
  _debug.log("onOrientationData") << "t: " << timestamp << "rot: " << rotation << std::endl;
}

void MyoUpdater::onAccelerometerData(MyoPtr dev, uint64_t timestamp, const myo::Vector3<float> &accel) {
  if (!_settings.outputAccel) {
    return;
  }
  _manager[dev].data.accel = accel;
  _debug.log("onAccelerometerData") << "t: " << timestamp << "accel: " << accel << std::endl;
}

void MyoUpdater::onGyroscopeData(MyoPtr dev, uint64_t timestamp, const myo::Vector3<float> &gyro) {
  _manager[dev].data.gyro = gyro;
  _debug.log("onGyroscopeData") << "t: " << timestamp << "gyro: " << gyro << std::endl;
}

void MyoUpdater::onRssi(MyoPtr dev, uint64_t timestamp, int8_t rssi) {
  _manager[dev].data.rssi = rssi;
  _debug.log("onRssi") << "t: " << timestamp << "rssi: " << rssi << std::endl;
}

void MyoUpdater::onEmgData(MyoPtr dev, uint64_t timestamp, const int8_t *emg) {
  auto& emgData = _manager[dev].data.emg;
  for (auto i = 0; i < emgLength; i++) {
    emgData[i] = emg[i];
  }
  _debug.log("onEmgData") << "t: " << timestamp << "data: " << emgData << std::endl;
}
