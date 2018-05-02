//
//  MyoCHOP.cpp
//  MyoCHOP
//
//  Created by tekt on 4/17/18.
//

#include "MyoCHOP.h"
#include <string>

static const char applicationId[] = "com.optexture.myochop";

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
    std::cout << "Initializing MyoCHOP" << std::endl;
    // Return a new instance of your class every time this is called.
    // It will be called once per CHOP that is using the .dll
    return new MyoCHOP(info);
  }

  DLLEXPORT
  void
  DestroyCHOPInstance(CHOP_CPlusPlusBase* instance)
  {
    std::cout << "Destroying MyoCHOP" << std::endl;
    // Delete the instance here, this will be called when
    // Touch is shutting down, when the CHOP using that instance is deleted, or
    // if the CHOP loads a different DLL
    delete (MyoCHOP*)instance;
  }

}

MyoCHOP::MyoCHOP(const OP_NodeInfo* info) {
  std::cerr << "BEGIN MyoCHOP::constructor" << std::endl;
  _debug = std::make_unique<MyoDebug>(_settings);
  _updater = std::make_unique<MyoUpdater>(_manager, _settings, *_debug);
  std::cerr << "END MyoCHOP::constructor" << std::endl;
}
MyoCHOP::~MyoCHOP() {
  std::cerr << "BEGIN MyoCHOP::destructor" << std::endl;
  deinitialize();
  std::cerr << "END MyoCHOP::destructor" << std::endl;
}

void MyoCHOP::getGeneralInfo(CHOP_GeneralInfo *info) {
  //std::cerr << "BEGIN MyoCHOP::getGeneralInfo" << std::endl;
  info->cookEveryFrameIfAsked = _settings.active;
  info->timeslice = true;
  //std::cerr << "END MyoCHOP::getGeneralInfo" << std::endl;
}

void MyoCHOP::setupParameters(OP_ParameterManager *manager) {
  std::cerr << "BEGIN MyoCHOP::setupParameters" << std::endl;
  MyoSettings::setUpParameters(manager);
  std::cerr << "END MyoCHOP::setupParameters" << std::endl;
}

bool MyoCHOP::getOutputInfo(CHOP_OutputInfo *info) {
  //std::cerr << "BEGIN MyoCHOP::getOutputInfo" << std::endl;
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
  //std::cerr << "END MyoCHOP::getOutputInfo" << std::endl;
  return true;
}

const char* MyoCHOP::getChannelName(int32_t index, void *reserved) {
  auto deviceIndex = index / static_cast<std::size_t>(OutputChan::numOutputs);
  auto chan = static_cast<OutputChan>(index % static_cast<std::size_t>(OutputChan::numOutputs));
  return MyoData::getChannelName(deviceIndex, chan);
}

void MyoCHOP::initialize() {
  std::cerr << "BEGIN MyoCHOP::initialize" << std::endl;
  std::cerr << "  MyoCHOP::initialize constructing myo::Hub" << std::endl;
  _hub = std::make_unique<myo::Hub>(applicationId);
  std::cerr << "  MyoCHOP::initialize finished constructing myo::Hub" << std::endl;
  std::cerr << "  MyoCHOP::initialize adding listener to hub" << std::endl;
  _hub->addListener(_updater.get());
  std::cerr << "  MyoCHOP::initialize finished adding listener to hub" << std::endl;
  std::cerr << "END MyoCHOP::initialize" << std::endl;
}

void MyoCHOP::deinitialize() {
  std::cerr << "BEGIN MyoCHOP::deinitialize" << std::endl;
  if (_hub) {
    if (_updater) {
      _hub->removeListener(_updater.get());
      _updater = nullptr;
    }
    _hub = nullptr;
  }
  _manager.clear();
  std::cerr << "END MyoCHOP::deinitialize" << std::endl;
}

void MyoCHOP::execute(const CHOP_Output *output,
                      OP_Inputs *inputs, void *reserved) {
  _debug->log() << "BEGIN MyoCHOP::execute" << std::endl;
  _debug->log() << "  MyoCHOP::execute updating initialization status" << std::endl;
  if (_settings.active) {
    if (!_hub) {
      initialize();
    }
  } else if (_hub || !_manager.empty()) {
    deinitialize();
  }
  if (!_hub) {
    _debug->log() << "END MyoCHOP::execute (NO HUB!)" << std::endl;
    return;
  }
  _debug->log() << "  MyoCHOP::execute finished updating initialization status" << std::endl;
  _debug->log() << "  MyoCHOP::execute setting locking policy" << std::endl;
  _hub->setLockingPolicy(_settings.enableLocking ?
                         myo::Hub::lockingPolicyStandard :
                         myo::Hub::lockingPolicyNone);
  _debug->log() << "  MyoCHOP::execute finished setting locking policy" << std::endl;
  _debug->log() << "  MyoCHOP::execute running hub for interval " << _settings.interval << std::endl;
  _hub->run(_settings.interval);
  _debug->log() << "  MyoCHOP::execute finished running hub for interval" << std::endl;
  _debug->log() << "  MyoCHOP::execute iterating devices (" << _manager.count() << ")" << std::endl;
  for (std::size_t deviceIndex = 0;
       deviceIndex < _manager.count();
       deviceIndex++) {
    _debug->log() << "    MyoCHOP::execute handling device " << deviceIndex << std::endl;
    auto& device = _manager.devices()[deviceIndex];
    _debug->log() << "      MyoCHOP::execute applying settings" << std::endl;
    device.applySettings(_settings);
    _debug->log() << "      MyoCHOP::execute finished applying settings" << std::endl;
    _debug->log() << "      MyoCHOP::execute writing channels" << std::endl;
    device.data.writeToChannels(output, deviceIndex);
    _debug->log() << "      MyoCHOP::execute finished writing channels" << std::endl;
    _debug->log() << "    MyoCHOP::execute finished handling device " << deviceIndex << std::endl;
  }
  _debug->log() << "  MyoCHOP::execute finished iterating devices" << std::endl;
  _debug->log() << "END MyoCHOP::execute" << std::endl;
}

int32_t MyoCHOP::getNumInfoCHOPChans() {
  //_debug->log() << "CALLED MyoCHOP::getNumInfoCHOPChans" << std::endl;
  return 0;
}

void MyoCHOP::getInfoCHOPChan(int index, OP_InfoCHOPChan *chan) {
  //_debug->log() << "CALLED MyoCHOP::getInfoCHOPChan(" << index << ")" << std::endl;
}

bool MyoCHOP::getInfoDATSize(OP_InfoDATSize *infoSize) {
  //_debug->log() << "CALLED MyoCHOP::getInfoDATSize" << std::endl;
  return false;
}

void MyoCHOP::getInfoDATEntries(int32_t index, int32_t nEntries, OP_InfoDATEntries *entries) {}

void MyoCHOP::pulsePressed(const char *name) {
  _debug->log() << "CALLED MyoCHOP::pulsePressed(" << name << ")" << std::endl;
  //...
}
