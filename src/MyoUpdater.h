//
//  MyoUpdater.hpp
//  MyoCHOP
//
//  Created by tekt on 4/18/18.
//

#pragma once

#include "Common.h"
#include "MyoData.h"
#include "MyoManager.h"

class MyoUpdater : public myo::DeviceListener {
public:
  MyoUpdater(MyoManager& manager) : _manager(manager) {}
  virtual ~MyoUpdater() {}

  /// Called when a Myo has been paired.
  /// @param dev The Myo for this event.
  /// @param timestamp The timestamp of the event. Timestamps are 64 bit unsigned integers that correspond to a number
  /// of microseconds since some (unspecified) period in time. Timestamps are monotonically non-decreasing.
  /// @param firmwareVersion The firmware version of \a myo.
  void onPair(MyoPtr dev, uint64_t timestamp, myo::FirmwareVersion firmwareVersion) override;

  /// Called when a Myo has been unpaired.
  /// @param dev The Myo for this event.
  /// @param timestamp The timestamp of the event. Timestamps are 64 bit unsigned integers that correspond to a number
  /// of microseconds since some (unspecified) period in time. Timestamps are monotonically non-decreasing.
  void onUnpair(MyoPtr dev, uint64_t timestamp) override;

  /// Called when a paired Myo has been connected.
  /// @param dev The Myo for this event.
  /// @param timestamp The timestamp of the event. Timestamps are 64 bit unsigned integers that correspond to a number
  /// of microseconds since some (unspecified) period in time. Timestamps are monotonically non-decreasing.
  /// @param firmwareVersion The firmware version of \a myo.
  void onConnect(MyoPtr dev, uint64_t timestamp, myo::FirmwareVersion firmwareVersion) override;

  /// Called when a paired Myo has been disconnected.
  /// @param dev The Myo for this event.
  /// @param timestamp The timestamp of the event. Timestamps are 64 bit unsigned integers that correspond to a number
  /// of microseconds since some (unspecified) period in time. Timestamps are monotonically non-decreasing.
  void onDisconnect(MyoPtr dev, uint64_t timestamp) override;

  /// Called when a paired Myo recognizes that it is on an arm.
  /// @param dev The Myo for this event.
  /// @param timestamp The timestamp of the event. Timestamps are 64 bit unsigned integers that correspond to a number
  /// of microseconds since some (unspecified) period in time. Timestamps are monotonically non-decreasing.
  /// @param arm The identified Arm of \a myo.
  /// @param xDirection The identified XDirection of \a myo.
  void onArmSync(MyoPtr dev, uint64_t timestamp, myo::Arm arm, myo::XDirection xDirection) override;

  /// Called when a paired Myo is moved or removed from the arm.
  /// @param dev The Myo for this event.
  /// @param timestamp The timestamp of the event. Timestamps are 64 bit unsigned integers that correspond to a number
  /// of microseconds since some (unspecified) period in time. Timestamps are monotonically non-decreasing.
  void onArmUnsync(MyoPtr dev, uint64_t timestamp) override;

  /// Called when a paired Myo becomes unlocked.
  /// @param dev The Myo for this event.
  /// @param timestamp The timestamp of the event. Timestamps are 64 bit unsigned integers that correspond to a number
  /// of microseconds since some (unspecified) period in time. Timestamps are monotonically non-decreasing.
  void onUnlock(MyoPtr dev, uint64_t timestamp) override;

  /// Called when a paired Myo becomes locked.
  /// @param dev The Myo for this event.
  /// @param timestamp The timestamp of the event. Timestamps are 64 bit unsigned integers that correspond to a number
  /// of microseconds since some (unspecified) period in time. Timestamps are monotonically non-decreasing.
  void onLock(MyoPtr dev, uint64_t timestamp) override;

  /// Called when a paired Myo has provided a new pose.
  /// @param dev The Myo for this event.
  /// @param timestamp The timestamp of the event. Timestamps are 64 bit unsigned integers that correspond to a number
  /// of microseconds since some (unspecified) period in time. Timestamps are monotonically non-decreasing.
  /// @param pose The identified Pose of \a myo.
  void onPose(MyoPtr dev, uint64_t timestamp, myo::Pose pose) override;

  /// Called when a paired Myo has provided new orientation data.
  /// @param dev The Myo for this event.
  /// @param timestamp The timestamp of the event. Timestamps are 64 bit unsigned integers that correspond to a number
  /// of microseconds since some (unspecified) period in time. Timestamps are monotonically non-decreasing.
  /// @param rotation The orientation data of \a myo, as a Quaternion.
  void onOrientationData(MyoPtr dev, uint64_t timestamp, const myo::Quaternion<float>& rotation) override;

  /// Called when a paired Myo has provided new accelerometer data in units of g.
  /// @param dev The Myo for this event.
  /// @param timestamp The timestamp of the event. Timestamps are 64 bit unsigned integers that correspond to a number
  /// of microseconds since some (unspecified) period in time. Timestamps are monotonically non-decreasing.
  /// @param accel The accelerometer data of \a myo, in units of g.
  void onAccelerometerData(MyoPtr dev, uint64_t timestamp, const myo::Vector3<float>& accel) override;

  /// Called when a paired Myo has provided new gyroscope data in units of deg/s.
  /// @param dev The Myo for this event.
  /// @param timestamp The timestamp of the event. Timestamps are 64 bit unsigned integers that correspond to a number
  /// of microseconds since some (unspecified) period in time. Timestamps are monotonically non-decreasing.
  /// @param gyro The gyroscope data of \a myo, in units of deg/s.
  void onGyroscopeData(MyoPtr dev, uint64_t timestamp, const myo::Vector3<float>& gyro) override;

  /// Called when a paired Myo has provided a new RSSI value.
  /// @param dev The Myo for this event.
  /// @param timestamp The timestamp of the event. Timestamps are 64 bit unsigned integers that correspond to a number
  /// of microseconds since some (unspecified) period in time. Timestamps are monotonically non-decreasing.
  /// @param rssi The RSSI (received signal strength indication) of \a myo.
  /// @see Myo::requestRssi() to request an RSSI value from the Myo.
  void onRssi(MyoPtr dev, uint64_t timestamp, int8_t rssi) override;

  /// Called when a paired Myo has provided new EMG data.
  /// @param dev The Myo for this event.
  /// @param timestamp The timestamp of the event. Timestamps are 64 bit unsigned integers that correspond to a number
  /// of microseconds since some (unspecified) period in time. Timestamps are monotonically non-decreasing.
  /// @param emg An array of 8 elements, each corresponding to one sensor.
  void onEmgData(MyoPtr dev, uint64_t timestamp, const int8_t* emg) override;

private:
  MyoManager& _manager;
};
