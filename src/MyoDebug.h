//
//  MyoDebug.h
//  MyoCHOP
//
//  Created by tekt on 4/29/18.
//

#pragma once

#include "Common.h"
#include "MyoSettings.h"
#include "NullOStream.h"

class MyoDebug {
public:
  explicit MyoDebug(const MyoSettings& settings)
  : _settings(settings) { }

  std::ostream& log(const char* action = nullptr);
private:
  const MyoSettings& _settings;
  NulOStream _nullStream;
};
