#include <Servo.h>
#include <limits.h>

// In Arduino, all the files are concatenated,
// which means the following global variables
// will be available across all the files.
// (Ugly, but it's quite handy for smaller projects like this.)

#define WARNING_MIN_DISTANCE 0.5
#define BRAKING_MIN_DISTANCE 0.2
#define ULTRASONIC_TRIGGER_PIN 2
#define ULTRASONIC_ECHO_PIN 3
// All the variables in the program which represent time
// are in microseconds.
#define SECOND 1000000
#define BELL_PIN 8
#define BRAKE_PIN 9
#define BRAKE_BRAKING_POS 5
#define BRAKE_NOTBRAKING_POS 30
#define WARNING_COOLDOWN (SECOND)
#define BRAKING_COOLDOWN (SECOND)

unsigned long currentTime = 0;
long previousTime = 0;
unsigned long deltaTime = 0;

enum class AebsState {
  failure,
  outOfRange,
  warning,
  braking
};

Servo brake;

void setup() {
  Serial.begin(9600);
  pinMode(ULTRASONIC_TRIGGER_PIN, OUTPUT);
  pinMode(ULTRASONIC_ECHO_PIN, INPUT);
  pinMode(BELL_PIN, OUTPUT);
  brake.attach(BRAKE_PIN);
}

void loop () {
  currentTime = micros();
  // Don't let currentTime overflow the maximum value of "long",
  // since it would cause errors in places where negative numbers
  // are used thus unsigned long cannot be used.
  // Also change previousTime because otherwise deltaTime would have
  // a value which is incredibly inaccurate.
  if (currentTime > LONG_MAX) {
    previousTime -= LONG_MAX;
    currentTime -= LONG_MAX;
  }
  deltaTime = currentTime - previousTime;
  
  double distance = getDistance();
  auto aebsState = getAebsState(distance);
  setBrakeAccordingToState(aebsState);
  playTheRespectiveTune(aebsState);

  previousTime = currentTime;
}
