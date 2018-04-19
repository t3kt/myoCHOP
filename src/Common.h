//
//  Common.h
//  MyoCHOP
//
//  Created by tekt on 4/17/18.
//

#pragma once

#include <cstddef>
#include <myo/myo.hpp>

using MyoPtr = myo::Myo*;

const std::size_t emgLength = 8;

namespace Page {

  extern const char myo[];
  extern const char outputs[];

}

const std::size_t numPoses = libmyo_num_poses;

namespace ParName {

  extern const char active[];
  extern const char interval[];
  extern const char enableLocking[];

  extern const char outputArm[];
  extern const char outputAccel[];
  extern const char outputGyro[];
  extern const char outputOrientation[];
  extern const char outputOrientationQuat[];
  extern const char outputPose[];
  extern const char outputEmg[];
  extern const char outputSync[];
  extern const char outputRssi[];
  extern const char outputLocked[];
  extern const char outputDirection[];

}

enum class OutputChan : std::size_t {
  synced,
  arm,
  direction,
  locked,
  rssi,
  accelX, accelY, accelZ,
  gyroX, gyroY, gyroZ,
  orientX, orientY, orientZ,
  orientQuatX, orientQuatY, orientQuatZ, orientQuatW,
  poseRest, poseFist, poseWaveIn, poseWaveOut,
  poseFingersSpread, poseDoubleTap,
  emg0, emg1, emg2, emg3, emg4, emg5, emg6, emg7,

  numOutputs,
};
