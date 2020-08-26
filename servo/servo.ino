// Sketch supports Arduino UNO/NANO schematic
#include <Servo.h>

#define TILT_CHANNEL 0
#define PAN_CHANNEL 1

#define SERVO_TILT_PIN 9  // Pin needs to support digital PWM
#define SERVO_PAN_PIN 10  // Pin needs to support digital PWM
#define INITIAL_SERVO_DEGREE 90

#define SERIAL_BPS 57600

char serial_char = 0;
char next_data = 0;

unsigned long time_since_sent = 0;

Servo servo_tilt, servo_pan;

void setup()
{
    // Attach servo to their pins
    servo_tilt.attach(SERVO_TILT_PIN);
    servo_pan.attach(SERVO_PAN_PIN);

    //Initially put the servos both at 90 degress
    servo_tilt.write(INITIAL_SERVO_DEGREE);  
    servo_pan.write(INITIAL_SERVO_DEGREE);

    //Set up a serial connection
    Serial.begin(SERIAL_BPS);
}

void loop(){
    // loop() reads data from serial port and identifies the corresponding servo ID
    // It then updates the servo according to the transmitted info
    // If the command character is not the pan or tilt servo ID, it is ignored.
    if (Serial.available() > 0) {
        serial_char = Serial.read();
        if (serial_char == TILT_CHANNEL) {
            while (Serial.available() > 0) {
                servo_tilt.write(Serial.read());
            }
            Serial.write(next_data);
            next_data = 1;
            time_since_sent = millis();
        }
        else if (serial_char == PAN_CHANNEL){
            while (Serial.available() > 0) {
                servo_pan.write(Serial.read());
            }
            Serial.write(next_data);
            next_data = 0;
            time_since_sent = millis();
        }
    } else if (millis() - time_since_sent > 1000) {
        Serial.write(next_data);
        if (next_data == 0) {
            next_data = 1;
        } else {
            next_data = 0;
        }
        time_since_sent = millis();
    }
}
