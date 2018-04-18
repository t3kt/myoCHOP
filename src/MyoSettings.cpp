//
//  MyoSettings.cpp
//  MyoCHOP
//
//  Created by tekt on 4/17/18.
//

#include "MyoSettings.h"
#include <assert.h>

static
void addBoolParameter(OP_ParameterManager *manager,
                      const char *name,
                      const char *page,
                      bool defaultValue) {
  OP_NumericParameter param(name);
  param.page = page;
  param.defaultValues[0] = static_cast<double>(defaultValue);
  auto result = manager->appendToggle(param);
  assert(result == OP_ParAppendResult::Success);
}

void MyoSettings::setUpParameters(OP_ParameterManager *manager) {
  addBoolParameter(manager, ParName::active, Page::myo, true);

  addBoolParameter(manager, ParName::outputArm, Page::outputs, true);
  addBoolParameter(manager, ParName::outputAccel, Page::outputs, true);
  addBoolParameter(manager, ParName::outputGyro, Page::outputs, true);
  addBoolParameter(manager, ParName::outputOrientation, Page::outputs, true);
  addBoolParameter(manager, ParName::outputOrientationQuat, Page::outputs, false);
  addBoolParameter(manager, ParName::outputPose, Page::outputs, false);
  addBoolParameter(manager, ParName::outputEmg, Page::outputs, false);
  addBoolParameter(manager, ParName::outputSync, Page::outputs, true);
  addBoolParameter(manager, ParName::outputRssi, Page::outputs, false);
  addBoolParameter(manager, ParName::outputDirection, Page::outputs, false);
}

MyoSettings::MyoSettings()
: active(true)
, outputArm(true)
, outputAccel(true)
, outputGyro(true)
, outputOrientation(true)
, outputOrientationQuat(false)
, outputPose(false)
, outputEmg(false)
, outputSync(true)
, outputRssi(false)
, outputDirection(false) { }

void MyoSettings::loadValuesFromParameters(OP_Inputs *inputs) {
  active = static_cast<bool>(inputs->getParInt(ParName::active));

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
