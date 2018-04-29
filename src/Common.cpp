//
//  Common.cpp
//  MyoCHOP
//
//  Created by tekt on 4/18/18.
//

#include "Common.h"

namespace Page {

  const char myo[] = "Myo";
  const char outputs[] = "Outputs";

}

namespace ParName {
  const char active[] = "Active";
  const char interval[] = "Interval";
  const char enableLocking[] = "Enablelocking";
  const char enableLogging[] = "Enablelogging";
  const char outputArm[] = "Outputarm";
  const char outputAccel[] = "Outputaccel";
  const char outputGyro[] = "Outputgyro";
  const char outputOrientation[] = "Outputorientation";
  const char outputOrientationQuat[] = "Outputorientationquat";
  const char outputPose[] = "Outputpose";
  const char outputEmg[] = "Outputemg";
  const char outputSync[] = "Outputsync";
  const char outputRssi[] = "Outputrssi";
  const char outputLocked[] = "Outputlocked";
  const char outputDirection[] = "Outputdirection";
}

std::ostream&
operator<<(std::ostream& os,
           const myo::FirmwareVersion& value) {
  return os << value.firmwareVersionMajor << "."
  << value.firmwareVersionMinor << "."
  << value.firmwareVersionPatch << "."
  << value.firmwareVersionHardwareRev;
}

std::ostream&
operator<<(std::ostream& os,
           const myo::Arm& value) {
  switch (value) {
    case myo::armLeft:
      return os << "left";
    case myo::armRight:
      return os << "right";
    case myo::armUnknown:
    default:
      return os << "unknown";
  }
}

std::ostream&
operator<<(std::ostream& os,
           const myo::XDirection& value) {
  switch (value) {
    case myo::xDirectionTowardElbow:
      return os << "elbow";
    case myo::xDirectionTowardWrist:
      return os << "wrist";
    case myo::xDirectionUnknown:
    default:
      return os << "unknown";
  }
}

std::ostream&
operator<<(std::ostream& os,
           const EmgArray& value) {
  os << "(";
  for (std::size_t i = 0; i < emgLength; i++) {
    if (i > 0) {
      os << ", ";
    }
    os <<  static_cast<int>(value[i]);
  }
  return os << ")";
}
