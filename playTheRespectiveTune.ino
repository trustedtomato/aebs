void playTheRespectiveTune (AebsState state) {
  static AebsState lastState { AebsState::failure };
  static long posInCycle = 0;
  static long lastTriggeredBellAt = 0;
  static PinWriter bellTrigger{ BELL_PIN };

  posInCycle += deltaTime;

  // After enough time has passed for the alarm
  // to get triggered, reset bell trigger.
  if (posInCycle - lastTriggeredBellAt > 5) {
    bellTrigger.write(LOW);
  }
  
  switch(state) {
    case AebsState::failure:
      // The tune cycle should be half second.
      while (posInCycle > SECOND / 4) {
        posInCycle -= SECOND / 4;
        lastTriggeredBellAt -= SECOND / 4;
      }
      // In the first quarter second, it should have a sound.
      if (posInCycle < SECOND / 8) {
        // Beep with around 440Hz.
        if(posInCycle - lastTriggeredBellAt > SECOND / 220) {
          bellTrigger.write(HIGH);
          lastTriggeredBellAt = posInCycle;
        }
      }
      // In the second quarter second, it should be silent.
      break;
    case AebsState::warning:
      // The tune cycle should be half second.
      while (posInCycle > SECOND / 8) {
        posInCycle -= SECOND / 8;
        lastTriggeredBellAt -= SECOND / 8;
      }
      // In the first quarter second, it should have a sound.
      if (posInCycle < SECOND / 16) {
        // Beep with around 440Hz.
        if(posInCycle - lastTriggeredBellAt > SECOND / 880) {
          bellTrigger.write(HIGH);
          lastTriggeredBellAt = posInCycle;
        }
      }
      // In the second quarter second, it should be silent.
      break;
    case AebsState::braking:
      // The tune cycle should be half second.
      while (posInCycle > SECOND / 16) {
        posInCycle -= SECOND / 16;
        lastTriggeredBellAt -= SECOND / 16;
      }
      // In the first quarter second, it should have a sound.
      if (posInCycle < SECOND / 32) {
        // Beep with around 440Hz.
        if(posInCycle - lastTriggeredBellAt > SECOND / 880) {
          bellTrigger.write(HIGH);
          lastTriggeredBellAt = posInCycle;
        }
      }
      // In the second quarter second, it should be silent.
      break;
  }
}
