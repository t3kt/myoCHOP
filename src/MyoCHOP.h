//
//  MyoCHOP.hpp
//  MyoCHOP
//
//  Created by tekt on 4/17/18.
//

#pragma once

#include <memory>
#include "CHOP_CPlusPlusBase.h"
#include "MyoData.h"
#include "MyoManager.h"
#include "MyoSettings.h"
#include "MyoUpdater.h"

class MyoCHOP : public CHOP_CPlusPlusBase {
public:
  MyoCHOP(const OP_NodeInfo* info);
  virtual ~MyoCHOP();

  virtual void    getGeneralInfo(CHOP_GeneralInfo* ) override;
  virtual bool    getOutputInfo(CHOP_OutputInfo*) override;
  virtual const char*  getChannelName(int32_t index, void* reserved) override;

  virtual void    execute(const CHOP_Output*,
                          OP_Inputs*,
                          void* reserved) override;


  virtual int32_t getNumInfoCHOPChans() override;
  virtual void    getInfoCHOPChan(int index,
                                  OP_InfoCHOPChan* chan) override;

  virtual bool    getInfoDATSize(OP_InfoDATSize* infoSize) override;
  virtual void    getInfoDATEntries(int32_t index,
                                    int32_t nEntries,
                                    OP_InfoDATEntries* entries) override;

  virtual void    setupParameters(OP_ParameterManager* manager) override;
  virtual void    pulsePressed(const char* name) override;
private:
  MyoSettings _settings;
  std::unique_ptr<myo::Hub> _hub;
  MyoManager _manager;
  std::unique_ptr<MyoUpdater> _updater;
};
