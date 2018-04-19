//
//  MyoData.cpp
//  MyoCHOP
//
//  Created by tekt on 4/17/18.
//

#include "MyoData.h"
#include <vector>

MyoData::MyoData()
: synced(false)
, arm(myo::armUnknown)
, direction(myo::xDirectionUnknown)
, locked(false)
, rssi(0) {}

template<typename T>
void writeChannel(const CHOP_Output *output,
                  std::size_t offset,
                  OutputChan chan,
                  T value) {
  auto i = offset + static_cast<std::size_t>(chan);
  if (i < output->numChannels) {
    output->channels[i][0] = static_cast<double>(value);
  }
}

static myo::Vector3<float> quaternionToVector(const myo::Quaternion<float>& quat) {
  // Calculate Euler angles (roll, pitch, and yaw) from the unit quaternion.
  float yaw = atan2(2.0f * (quat.w() * quat.z() + quat.x() * quat.y()),
                    1.0f - 2.0f * (quat.y() * quat.y() + quat.z() * quat.z()));
  float pitch = asin(2.0f * (quat.w() * quat.y() - quat.z() * quat.x()));
  float roll = atan2(2.0f * (quat.w() * quat.x() + quat.y() * quat.z()),
                     1.0f - 2.0f * (quat.x() * quat.x() + quat.y() * quat.y()));
  return myo::Vector3<float>(yaw, pitch, roll);
}

void MyoData::writeToChannels(const CHOP_Output *output,
                              std::size_t deviceIndex) const {
  auto offset = deviceIndex * static_cast<std::size_t>(OutputChan::numOutputs);
  writeChannel(output, offset, OutputChan::synced, synced);
  writeChannel(output, offset, OutputChan::arm, arm);
  writeChannel(output, offset, OutputChan::direction, direction);
  writeChannel(output, offset, OutputChan::locked, locked);
  writeChannel(output, offset, OutputChan::rssi, rssi);

  writeChannel(output, offset, OutputChan::accelX, accel.x());
  writeChannel(output, offset, OutputChan::accelY, accel.y());
  writeChannel(output, offset, OutputChan::accelZ, accel.z());

  writeChannel(output, offset, OutputChan::gyroX, gyro.x());
  writeChannel(output, offset, OutputChan::gyroY, gyro.y());
  writeChannel(output, offset, OutputChan::gyroZ, gyro.z());

  auto orientVec = quaternionToVector(orient);

  writeChannel(output, offset, OutputChan::orientX, orientVec.x());
  writeChannel(output, offset, OutputChan::orientY, orientVec.y());
  writeChannel(output, offset, OutputChan::orientZ, orientVec.z());

  writeChannel(output, offset, OutputChan::orientQuatX, orient.x());
  writeChannel(output, offset, OutputChan::orientQuatY, orient.y());
  writeChannel(output, offset, OutputChan::orientQuatZ, orient.z());
  writeChannel(output, offset, OutputChan::orientQuatZ, orient.w());

  writeChannel(output, offset, OutputChan::poseRest, poses[myo::Pose::rest]);
  writeChannel(output, offset, OutputChan::poseFist, poses[myo::Pose::fist]);
  writeChannel(output, offset, OutputChan::poseWaveIn, poses[myo::Pose::waveIn]);
  writeChannel(output, offset, OutputChan::poseWaveOut, poses[myo::Pose::waveOut]);
  writeChannel(output, offset, OutputChan::poseFingersSpread, poses[myo::Pose::fingersSpread]);
  writeChannel(output, offset, OutputChan::poseDoubleTap, poses[myo::Pose::doubleTap]);

  writeChannel(output, offset, OutputChan::emg0, emg[0]);
  writeChannel(output, offset, OutputChan::emg1, emg[1]);
  writeChannel(output, offset, OutputChan::emg2, emg[2]);
  writeChannel(output, offset, OutputChan::emg3, emg[3]);
  writeChannel(output, offset, OutputChan::emg4, emg[4]);
  writeChannel(output, offset, OutputChan::emg5, emg[5]);
  writeChannel(output, offset, OutputChan::emg6, emg[6]);
  writeChannel(output, offset, OutputChan::emg7, emg[7]);
}

std::string makeChannelName(std::size_t deviceIndex,
                            std::string suffix) {
  return "myo" + std::to_string(deviceIndex) + "/" + suffix;
}

class DeviceChannelNames {
public:
  DeviceChannelNames(std::size_t i) {
    setName(i, OutputChan::synced, "synced");
    setName(i, OutputChan::arm, "arm");
    setName(i, OutputChan::direction, "direction");
    setName(i, OutputChan::locked, "locked");
    setName(i, OutputChan::rssi, "rssi");

    setName(i, OutputChan::accelX, "accelX");
    setName(i, OutputChan::accelY, "accelY");
    setName(i, OutputChan::accelZ, "accelZ");

    setName(i, OutputChan::gyroX, "gyroX");
    setName(i, OutputChan::gyroY, "gyroY");
    setName(i, OutputChan::gyroZ, "gyroZ");

    setName(i, OutputChan::orientX, "orientX");
    setName(i, OutputChan::orientY, "orientY");
    setName(i, OutputChan::orientZ, "orientZ");

    setName(i, OutputChan::orientQuatX, "orientQuatX");
    setName(i, OutputChan::orientQuatY, "orientQuatY");
    setName(i, OutputChan::orientQuatZ, "orientQuatZ");
    setName(i, OutputChan::orientQuatW, "orientQuatW");

    setName(i, OutputChan::poseRest, "poseRest");
    setName(i, OutputChan::poseFist, "poseFist");
    setName(i, OutputChan::poseWaveIn, "poseWaveIn");
    setName(i, OutputChan::poseWaveOut, "poseWaveOut");
    setName(i, OutputChan::poseFingersSpread, "poseFingersSpread");
    setName(i, OutputChan::poseDoubleTap, "poseDoubleTap");

    setName(i, OutputChan::emg0, "emg0");
    setName(i, OutputChan::emg1, "emg1");
    setName(i, OutputChan::emg2, "emg2");
    setName(i, OutputChan::emg3, "emg3");
    setName(i, OutputChan::emg4, "emg4");
    setName(i, OutputChan::emg5, "emg5");
    setName(i, OutputChan::emg6, "emg6");
    setName(i, OutputChan::emg7, "emg7");
  }
  const char* operator[](OutputChan chan) const {
    return _names[static_cast<std::size_t>(chan)].c_str();
  }

private:
  void setName(std::size_t deviceIndex,
               OutputChan chan,
               std::string suffix) {
    _names[static_cast<std::size_t>(chan)]
      = makeChannelName(deviceIndex, suffix);
  }

  std::array<std::string, static_cast<std::size_t>(OutputChan::numOutputs)> _names;
};

static std::vector<DeviceChannelNames> deviceChannelNames;

const char* MyoData::getChannelName(std::size_t deviceIndex,
                                    OutputChan chan) {
  if (deviceIndex >= deviceChannelNames.size()) {
    deviceChannelNames.emplace_back(deviceIndex);
  }
  return deviceChannelNames[deviceIndex][chan];
}
