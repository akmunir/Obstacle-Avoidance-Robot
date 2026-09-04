#include <Arduino.h>
#include "obstacleAvoidance.h"

const float speedOfSound = 0.0343;

float getDistanceToObstacle() {
    float duration;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    duration = pulseIn(echoPin, HIGH);
    return (duration * speedOfSound) / 2; // x = vt, divided by 2 because the pulse moves forward and back and we just need it one way


}