// Sketch supports Arduino UNO/NANO schematic
#include <Servo.h>


#define SERVO_TILT_PIN 9  // Pin needs to support digital PWM
#define SERVO_PAN_PIN 10  // Pin needs to support.msg digital PWM
#define INITIAL_SERVO_DEGREE 90

Servo servo_tilt, servo_pan;

void setup()
{
    // Set random seed
    randomSeed(analogRead(0));

    // Attach servo to their pins
    servo_tilt.attach(SERVO_TILT_PIN);
    servo_pan.attach(SERVO_PAN_PIN);

    //Initially put the servos both at 90 degress
    servo_tilt.write(INITIAL_SERVO_DEGREE);  
    servo_pan.write(INITIAL_SERVO_DEGREE);
}

void loop(){
    // Set servo to random value between [0, 180] every second
    servo_tilt.write(random(180));
    servo_pan.write(random(180));
    delay(1000);
}
