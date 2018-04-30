//
//  MyoSettings.h
//  MyoCHOP
//
//  Created by tekt on 4/17/18.
//

#pragma once

#include "CHOP_CPlusPlusBase.h"
#include "Common.h"

class MyoSettings {
public:
  static void setUpParameters(OP_ParameterManager* manager);

  MyoSettings();
  explicit MyoSettings(OP_Inputs* inputs);

  bool active;
  uint32_t interval;
  bool enableLocking;
  bool enableLogging;

  bool outputArm;
  bool outputAccel;
  bool outputGyro;
  bool outputOrientation;
  bool outputOrientationQuat;
  bool outputPose;
  bool outputEmg;
  bool outputSync;
  bool outputRssi;
  bool outputDirection;
  
};

bool operator==(const MyoSettings& lhs, const MyoSettings& rhs);
inline bool operator!=(const MyoSettings& lhs, const MyoSettings& rhs){ return !(lhs == rhs); }
