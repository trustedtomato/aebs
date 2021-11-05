/**
 * Transforms the output of "getDistance" to "AebsState".
 */
AebsState getAebsState (double distance) {
  static long hadWarningStateAt = 0;
  static long hadBrakingStateAt = 0;
  static AebsState lastState { AebsState::failure };
  AebsState state;
  
  if (distance == -1) {
    state = AebsState::failure;
  } else if (distance == 0) {
    state = lastState;
  } else if (distance < BRAKING_MIN_DISTANCE) {
    hadBrakingStateAt = currentTime;
    state = AebsState::braking;
  } else if (distance < WARNING_MIN_DISTANCE) {
    hadWarningStateAt = currentTime;
    state = AebsState::warning;
  } else {
    state = AebsState::outOfRange;
  }

  lastState = state;
  if (
    hadBrakingStateAt != 0 &&
    currentTime - hadBrakingStateAt < BRAKING_COOLDOWN
  ) {
    return AebsState::braking;
  } else if (
    hadWarningStateAt != 0 &&
    currentTime - hadWarningStateAt < WARNING_COOLDOWN
  ) {
    return AebsState::warning;
  } else {
    return state;
  }
}
