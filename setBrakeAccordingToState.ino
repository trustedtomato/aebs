void setBrakeAccordingToState (AebsState state) {
  static ServoWriter brakeWriter { brake, BRAKE_BRAKING_POS };
  if (state == AebsState::braking) {
    brake.write(BRAKE_BRAKING_POS);
  } else {
    brake.write(BRAKE_NOTBRAKING_POS);
  }
}
