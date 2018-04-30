//
//  MyoDebug.cpp
//  MyoCHOP
//
//  Created by tekt on 4/29/18.
//

#include "MyoDebug.h"

std::ostream& MyoDebug::log(const char* action) {
  if (!_settings.enableLogging) {
    return _nullStream;
  }
  auto& os = std::cerr;
  if (action != nullptr) {
    os << action << " ";
  }
  return os;
}
