//
//  MyoCHOP.cpp
//  MyoCHOP
//
//  Created by tekt on 4/17/18.
//

#include "MyoCHOP.h"

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

MyoCHOP::MyoCHOP(const OP_NodeInfo* info) {}
MyoCHOP::~MyoCHOP() {}

void MyoCHOP::getGeneralInfo(CHOP_GeneralInfo *info) {
  info->cookEveryFrameIfAsked = true;
  info->timeslice = true;
}

void MyoCHOP::setupParameters(OP_ParameterManager *manager) {
  MyoSettings::setUpParameters(manager);
}

bool MyoCHOP::getOutputInfo(CHOP_OutputInfo *info) {
  info->numChannels = 1;

  // Since we are outputting a timeslice, the system will dictate
  // the numSamples and startIndex of the CHOP data
  //info->numSamples = 1;
  //info->startIndex = 0
  return true;
}

const char* MyoCHOP::getChannelName(int32_t index, void *reserved) {
  return "chan1";
}

void MyoCHOP::execute(const CHOP_Output *output, OP_Inputs *inputs, void *reserved) {
  //TODO: WRITE THIS!
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
