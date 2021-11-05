/**
 * Non-blocking  replacement for pulseIn().
 * "getPulse" returns the pulse length in microseconds
 * when the falling edge is detected. Otherwise returns 0.
 */
class PulseReader {
  public:
    int pin;
    long risingTime;
    int lastState{ LOW };
   
    explicit PulseReader(int _pin) : pin(_pin) {}

    unsigned long getPulse (long currentTime) {
      int state = digitalRead(this->pin);
      long pulseLength = 0;
  
      // On rising edge: record current time.
      if (this->lastState == LOW && state == HIGH) {
          risingTime = currentTime;
      }
  
      // On falling edge: report pulse length.
      if (this->lastState == HIGH && state == LOW) {
          pulseLength = currentTime - this->risingTime;
          // Correct when currentTime overflows and goes back to zero.
          while (pulseLength < 0) {
            pulseLength += LONG_MAX;
          }
      }
  
      this->lastState = state;
      return pulseLength;
    }
};
