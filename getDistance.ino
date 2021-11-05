/*
 * Calculates distance using the ultrasonic sensor.
 * If it is currently calculating the distance, returns 0,
 * if the ultrasonic sensor doesn't detect anything, returns -1,
 * otherwise returns the distance in meters.
 */
double getDistance () {
  static PulseReader ultrasonicEcho {ULTRASONIC_ECHO_PIN};
  static PinWriter ultrasonicTrigger {ULTRASONIC_TRIGGER_PIN};  
  static unsigned long posInCycle = 0;
  static unsigned long startedTriggeringAt = 0;
    
  posInCycle += deltaTime;

  // In the first 50 microseconds, just set the triggering to LOW to be safe.
  // After that, set the trigger pin to HIGH (to trigger the ultrasonic sensor),
  // and at least 10 microseconds after that
  // set the trigger pin to LOW again, and keep it that way
  // until the detection cycle resets.
  if ( posInCycle < 50 || (startedTriggeringAt > 0 && posInCycle - startedTriggeringAt >= 10)) {
    ultrasonicTrigger.write(LOW);
  } else if (ultrasonicTrigger.value == LOW) {
    startedTriggeringAt = posInCycle;
    ultrasonicTrigger.write(HIGH);
  }

  auto duration = ultrasonicEcho.getPulse(currentTime);

  // For some reason, the ultrasonic sensor sends
  // a huge echo signal when it doesn't detect anything.
  // This should be ignored.
  if (duration > 60000) {
    posInCycle = 0;
    startedTriggeringAt = 0;
    return -1;
  }
  // The duration is a realistic number,
  // the returned value should be the distance
  // which should be calculated from the duration
  // measured in microseconds.
  else if (duration > 0) {
    posInCycle = 0;
    startedTriggeringAt = 0;
    return duration * 0.034 / 2 / 100;
  }
  // If the posInCycle is way too big and the echo signal haven't
  // even started, that means that the ultrasonic waves
  // did not reach the receiver, so lets just restart the detection cycle.
  else if (posInCycle > 50000 && ultrasonicEcho.lastState == LOW) {
    posInCycle = 0;
    startedTriggeringAt = 0;
    return -1;
  }

  return 0;
};
