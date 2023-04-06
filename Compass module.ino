#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

/* Create a unique instance of the Adafruit_HMC5883_Unified sensor */
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

void setup(void)
{
Serial.begin(9600);
Serial.println("HMC5883 Magnetometer Test");
Serial.println("");

/* Initialize the sensor */
if(!mag.begin())
{
/* If the sensor cannot be detected, send error message and halt program execution */
Serial.println("No HMC5883 detected...make sure the sensor is properly connected");
while(true);
}
}

void loop(void)
{
/* Get a new sensor event */
sensors_event_t event;
mag.getEvent(&event);

/* Display the magnetic vector values in micro-Tesla (uT) */
Serial.print("X: ");
Serial.print(event.magnetic.x);
Serial.print(" ");
Serial.print("Y: ");
Serial.print(event.magnetic.y);
Serial.print(" ");
Serial.print("Z: ");
Serial.print(event.magnetic.z);
Serial.print(" ");
Serial.println("uT");

/* Calculate the heading when the magnetometer is level, then correct for signs of the axis. */
float heading = atan2(event.magnetic.y, event.magnetic.x);

/* Add the 'Declination Angle' to the heading to correct for the magnetic field error in your location */
float declinationAngle = 0.663;
heading += declinationAngle;

/* Correct for when signs are reversed */
if(heading < 0){
heading += 2PI;
}

/* Check for wrap due to the addition of declination */
if(heading > 2PI){
heading -= 2*PI;
}

/* Convert the heading from radians to degrees for readability */
float headingDegrees = heading * 180/M_PI;

/* Display the heading in degrees */
Serial.print("Heading (degrees): ");
Serial.println(headingDegrees);

/* Wait for 500 milliseconds before the next iteration */
delay(500);
}
