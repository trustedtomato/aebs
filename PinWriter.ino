/**
 * Wrapper around digitalWrite.
 * Remembers what was written to the pin last,
 * and does not perform the requested write operation
 * if it already has the given value.
 */
class PinWriter {
  public:
    int value;
    int pin;
    PinWriter(int _pin, int initialValue = LOW) : pin(_pin), value(initialValue) {}
    void write (int newValue) {
      if (this->value != newValue) {
        digitalWrite(this->pin, newValue);
        this->value = newValue;
      }
    }
};

/**
 * Wrapper around servo write.
 * Remembers what was written to the servo last,
 * and does not perform the requested write operation
 * if it already has the given value.
 */
class ServoWriter {
  public:
    Servo servo;
    int value;
    ServoWriter(Servo _servo, int initialValue) : servo(_servo), value(initialValue) {}
    void write (int newValue) {
      if (this->value != newValue) {
        this->servo.write(newValue);
        this->value = newValue;
      }
    }
};
