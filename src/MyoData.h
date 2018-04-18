//
//  MyoData.h
//  MyoCHOP
//
//  Created by tekt on 4/17/18.
//

#pragma once

#include <array>
#include <myo/myo.hpp>
#include "CHOP_CPlusPlusBase.h"
#include "Common.h"

using EmgArray = std::array<int8_t, emgLength>;
using PoseArray = std::array<bool, numPoses>;

class MyoData {
public:
  MyoData();

  void writeToChannels(CHOP_Output* output,
                       std::size_t deviceIndex) const;

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
