//
//  MyoSettings.hpp
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

  void loadValuesFromParameters(OP_Inputs* inputs);

  MyoSettings();

  bool active;
  uint32_t interval;
  bool enableLocking;

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
