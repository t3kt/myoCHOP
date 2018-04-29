//
//  MyoSettings.cpp
//  MyoCHOP
//
//  Created by tekt on 4/17/18.
//

#include "MyoSettings.h"
#include <assert.h>

static const uint32_t defaultInterval = 1000 / 60;

static
void addBoolParameter(OP_ParameterManager *manager,
                      const char *name,
                      const char *page,
                      bool defaultValue,
                      const char* label = nullptr) {
  OP_NumericParameter param(name);
  param.page = page;
  param.defaultValues[0] = static_cast<double>(defaultValue);
  param.label = label;
  auto result = manager->appendToggle(param);
  assert(result == OP_ParAppendResult::Success);
}

void MyoSettings::setUpParameters(OP_ParameterManager *manager) {
  addBoolParameter(manager, ParName::active, Page::myo, false);

  {
    OP_NumericParameter param(ParName::interval);
    param.page = Page::myo;
    param.label = "Update Interval";
    param.defaultValues[0] = defaultInterval;
    param.minSliders[0] = param.minValues[0] = 0;
    param.maxSliders[0] = param.maxValues[0] = 1000;
    param.clampMins[0] = true;
    param.clampMaxes[0] = true;
    auto result = manager->appendInt(param);
    assert(result == OP_ParAppendResult::Success);
  }

  addBoolParameter(manager, ParName::enableLocking, Page::myo, false,
                   "Enable Locking");
  addBoolParameter(manager, ParName::enableLogging, Page::myo, false,
                   "Enable Logging");

  addBoolParameter(manager, ParName::outputArm, Page::outputs, true,
                   "Output Arm");
  addBoolParameter(manager, ParName::outputAccel, Page::outputs, true,
                   "Output Accelerometer");
  addBoolParameter(manager, ParName::outputGyro, Page::outputs, true,
                   "Output Gyroscope");
  addBoolParameter(manager, ParName::outputOrientation, Page::outputs, true,
                   "Output Orientation (Vector)");
  addBoolParameter(manager, ParName::outputOrientationQuat, Page::outputs, false,
                   "Output Orientation (Quaternion)");
  addBoolParameter(manager, ParName::outputPose, Page::outputs, false,
                   "Output Pose");
  addBoolParameter(manager, ParName::outputEmg, Page::outputs, false,
                   "Output EMG");
  addBoolParameter(manager, ParName::outputSync, Page::outputs, true,
                   "Output Sync");
  addBoolParameter(manager, ParName::outputRssi, Page::outputs, false,
                   "Output RSSI");
  addBoolParameter(manager, ParName::outputDirection, Page::outputs, false,
                   "Output Direction");
}

MyoSettings::MyoSettings()
: active(false)
, enableLocking(false)
, enableLogging(true)
, outputArm(true)
, outputAccel(true)
, outputGyro(true)
, outputOrientation(true)
, outputOrientationQuat(false)
, outputPose(false)
, outputEmg(false)
, outputSync(true)
, outputRssi(false)
, outputDirection(false)
, interval(defaultInterval) { }

MyoSettings::MyoSettings(OP_Inputs *inputs) {
  active = static_cast<bool>(inputs->getParInt(ParName::active));
  enableLocking = static_cast<bool>(inputs->getParInt(ParName::enableLocking));
  enableLogging = static_cast<bool>(inputs->getParInt(ParName::interval));
  interval = inputs->getParInt(ParName::interval);

  outputArm = static_cast<bool>(inputs->getParInt(ParName::outputArm));
  outputAccel = static_cast<bool>(inputs->getParInt(ParName::outputAccel));
  outputGyro = static_cast<bool>(inputs->getParInt(ParName::outputGyro));
  outputOrientation = static_cast<bool>(inputs->getParInt(ParName::outputOrientation));
  outputOrientationQuat = static_cast<bool>(inputs->getParInt(ParName::outputOrientationQuat));
  outputPose = static_cast<bool>(inputs->getParInt(ParName::outputPose));
  outputEmg = static_cast<bool>(inputs->getParInt(ParName::outputEmg));
  outputSync = static_cast<bool>(inputs->getParInt(ParName::outputSync));
  outputRssi = static_cast<bool>(inputs->getParInt(ParName::outputRssi));
  outputDirection = static_cast<bool>(inputs->getParInt(ParName::outputDirection));
}

bool operator==(const MyoSettings& lhs, const MyoSettings& rhs) {
  return lhs.active == rhs.active
    && lhs.interval == rhs.interval
    && lhs.enableLocking == rhs.enableLocking
  && lhs.outputArm == rhs.outputArm
  && lhs.outputAccel == rhs.outputAccel
  && lhs.outputGyro == rhs.outputGyro
  && lhs.outputOrientation == rhs.outputOrientation
  && lhs.outputOrientationQuat == rhs.outputOrientationQuat
  && lhs.outputPose == rhs.outputPose
  && lhs.outputEmg == rhs.outputEmg
  && lhs.outputSync == rhs.outputSync
  && lhs.outputRssi == rhs.outputRssi
  && lhs.outputDirection == rhs.outputDirection;
}
