//
//  MyoCHOP.cpp
//  MyoCHOP
//
//  Created by tekt on 4/17/18.
//

#include "MyoCHOP.h"
#include <string>

static const std::string applicationId = "com.optexture.myochop";

extern "C" {
  DLLEXPORT
  int32_t
  GetCHOPAPIVersion(void)
  {
    // Always return CHOP_CPLUSPLUS_API_VERSION in this function.
    return CHOP_CPLUSPLUS_API_VERSION;
  }

  DLLEXPORT
  CHOP_CPlusPlusBase*
  CreateCHOPInstance(const OP_NodeInfo* info)
  {
    // Return a new instance of your class every time this is called.
    // It will be called once per CHOP that is using the .dll
    return new MyoCHOP(info);
  }

  DLLEXPORT
  void
  DestroyCHOPInstance(CHOP_CPlusPlusBase* instance)
  {
    // Delete the instance here, this will be called when
    // Touch is shutting down, when the CHOP using that instance is deleted, or
    // if the CHOP loads a different DLL
    delete (MyoCHOP*)instance;
  }

}

MyoCHOP::MyoCHOP(const OP_NodeInfo* info) {
  _updater = std::make_unique<MyoUpdater>(_manager, _settings);
}
MyoCHOP::~MyoCHOP() {
  deinitialize();
}

void MyoCHOP::getGeneralInfo(CHOP_GeneralInfo *info) {
  info->cookEveryFrameIfAsked = true;
  info->timeslice = true;
}

void MyoCHOP::setupParameters(OP_ParameterManager *manager) {
  MyoSettings::setUpParameters(manager);
}

bool MyoCHOP::getOutputInfo(CHOP_OutputInfo *info) {
  _settings = MyoSettings(info->opInputs);
  if (_settings.active) {
    info->numChannels = static_cast<int32_t>(_manager.count()) * static_cast<int32_t>(OutputChan::numOutputs);
  } else {
    info->numChannels = 0;
  }

  // Since we are outputting a timeslice, the system will dictate
  // the numSamples and startIndex of the CHOP data
  //info->numSamples = 1;
  //info->startIndex = 0
  return true;
}

const char* MyoCHOP::getChannelName(int32_t index, void *reserved) {
  auto deviceIndex = index / static_cast<std::size_t>(OutputChan::numOutputs);
  auto chan = static_cast<OutputChan>(index % static_cast<std::size_t>(OutputChan::numOutputs));
  return MyoData::getChannelName(deviceIndex, chan);
}

void MyoCHOP::initialize() {
  _hub = std::make_unique<myo::Hub>(applicationId);
  _hub->addListener(_updater.get());
}

void MyoCHOP::deinitialize() {
  if (_hub) {
    if (_updater) {
      _hub->removeListener(_updater.get());
      _updater = nullptr;
    }
    _hub = nullptr;
  }
  _manager.clear();
}

void MyoCHOP::execute(const CHOP_Output *output,
                      OP_Inputs *inputs, void *reserved) {
  if (_settings.active) {
    if (!_hub) {
      initialize();
    }
  } else {
    deinitialize();
  }
  if (!_hub) {
    return;
  }
  _hub->setLockingPolicy(_settings.enableLocking ?
                         myo::Hub::lockingPolicyStandard :
                         myo::Hub::lockingPolicyNone);
  _hub->run(_settings.interval);
  for (std::size_t deviceIndex = 0;
       deviceIndex < _manager.count();
       deviceIndex++) {
    auto& device = _manager.devices()[deviceIndex];
    device.applySettings(_settings);
    device.data.writeToChannels(output, deviceIndex);
  }
}

int32_t MyoCHOP::getNumInfoCHOPChans() {
  return 0;
}

void MyoCHOP::getInfoCHOPChan(int index, OP_InfoCHOPChan *chan) {}

bool MyoCHOP::getInfoDATSize(OP_InfoDATSize *infoSize) {
  return false;
}

void MyoCHOP::getInfoDATEntries(int32_t index, int32_t nEntries, OP_InfoDATEntries *entries) {}

void MyoCHOP::pulsePressed(const char *name) {
  //...
}
