//
//  MyoData.h
//  MyoCHOP
//
//  Created by tekt on 4/17/18.
//

#pragma once

#include <myo/myo.hpp>
#include "CHOP_CPlusPlusBase.h"
#include "Common.h"

class MyoData {
public:
  static const char* getChannelName(std::size_t deviceIndex,
                                    OutputChan chan);

  MyoData();

  void writeToChannels(const CHOP_Output* output,
                       std::size_t deviceIndex) const;

  void setPose(myo::Pose pose) {
    poses[static_cast<std::size_t>(pose.type())] = true;
  }

  void resetPoses() {
    poses.fill(false);
  }

  bool synced;
  myo::Arm arm;
  myo::XDirection direction;
  bool locked;
  int8_t rssi;

  myo::Vector3<float> accel;
  myo::Vector3<float> gyro;
  myo::Quaternion<float> orient;
  PoseArray poses;
  EmgArray emg;
};
