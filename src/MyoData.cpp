//
//  MyoData.cpp
//  MyoCHOP
//
//  Created by tekt on 4/17/18.
//

#include "MyoData.h"

MyoData::MyoData()
: synced(false)
, arm(myo::armUnknown)
, direction(myo::xDirectionUnknown)
, locked(false)
, rssi(0) {}

template<typename T>
void writeChannel(CHOP_Output *output, std::size_t offset, OutputChan chan, T value) {
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

void MyoData::writeToChannels(CHOP_Output *output,
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