#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <SoftwareSerial.h>
SoftwareSerial BTserial(11, 12); // RX | TX
int sensorPin = A0;
int sensorValue = 0;
const int trigPin = 9;
const int echoPin = 10;
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;
long duration;
int distance;

// The TinyGPS++ object
TinyGPSPlus gps;
// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
ss.begin(GPSBaud);
BTserial.begin(9600);
}
void loop() {
  while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      // Clears the trigPin
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      // Sets the trigPin on HIGH state for 10 micro seconds
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      // Reads the echoPin, returns the sound wave travel time in microseconds
      duration = pulseIn(echoPin, HIGH);
      // Calculating the distance
      distance= duration*0.034/2;
      // Prints the distance on the Serial Monitor
      BTserial.print("Distance: ");
      BTserial.println(distance);
      // Latitude in degrees (double)
      BTserial.print("Latitude= ");
      BTserial.print(gps.location.lat(), 6);
      // Longitude in degrees (double)
      BTserial.print(" Longitude= ");
      BTserial.println(gps.location.lng(), 6);

      // Raw latitude in whole degrees
      BTserial.print("Raw latitude = ");
      BTserial.print(gps.location.rawLat().negative ? "-" : "+");
      BTserial.println(gps.location.rawLat().deg);
      // ... and billionths (u16/u32)
      BTserial.println(gps.location.rawLat().billionths);

      // Raw longitude in whole degrees
      BTserial.print("Raw longitude = ");
      BTserial.print(gps.location.rawLng().negative ? "-" : "+");
      BTserial.println(gps.location.rawLng().deg);
      // ... and billionths (u16/u32)
      BTserial.println(gps.location.rawLng().billionths);

      // Raw date in DDMMYY format (u32)
      BTserial.print("Raw date DDMMYY = ");
      BTserial.println(gps.date.value());

      // Year (2000+) (u16)
      BTserial.print("Year = ");
      BTserial.println(gps.date.year());
      // Month (1-12) (u8)
      BTserial.print("Month = ");
      BTserial.println(gps.date.month());
      // Day (1-31) (u8)
      BTserial.print("Day = ");
      BTserial.println(gps.date.day());

      // Raw time in HHMMSSCC format (u32)
      BTserial.print("Raw time in HHMMSSCC = ");
      BTserial.println(gps.time.value());

      // Hour (0-23) (u8)
      BTserial.print("Hour = ");
      BTserial.println(gps.time.hour());
      // Minute (0-59) (u8)
      BTserial.print("Minute = ");
      BTserial.println(gps.time.minute());
      // Second (0-59) (u8)
      BTserial.print("Second = ");
      BTserial.println(gps.time.second());
      // 100ths of a second (0-99) (u8)
      BTserial.print("Centisecond = ");
      BTserial.println(gps.time.centisecond());

      // Raw speed in 100ths of a knot (i32)
      BTserial.print("Raw speed in 100ths/knot = ");
      BTserial.println(gps.speed.value());
      // Speed in knots (double)
      BTserial.print("Speed in knots/h = ");
      BTserial.println(gps.speed.knots());
      // Speed in miles per hour (double)
      BTserial.print("Speed in miles/h = ");
      BTserial.println(gps.speed.mph());
      // Speed in meters per second (double)
      BTserial.print("Speed in m/s = ");
      BTserial.println(gps.speed.mps());
      // Speed in kilometers per hour (double)
      BTserial.print("Speed in km/h = ");
      BTserial.println(gps.speed.kmph());

      // Raw course in 100ths of a degree (i32)
      BTserial.print("Raw course in degrees = ");
      BTserial.println(gps.course.value());
      // Course in degrees (double)
      BTserial.print("Course in degrees = ");
      BTserial.println(gps.course.deg());

      // Raw altitude in centimeters (i32)
      BTserial.print("Raw altitude in centimeters = ");
      BTserial.println(gps.altitude.value());
      // Altitude in meters (double)
      BTserial.print("Altitude in meters = ");
      BTserial.println(gps.altitude.meters());
      // Altitude in miles (double)
      BTserial.print("Altitude in miles = ");
      BTserial.println(gps.altitude.miles());
      // Altitude in kilometers (double)
      BTserial.print("Altitude in kilometers = ");
      BTserial.println(gps.altitude.kilometers());
      // Altitude in feet (double)
      BTserial.print("Altitude in feet = ");
      BTserial.println(gps.altitude.feet());

      // Number of satellites in use (u32)
      BTserial.print("Number os satellites in use = ");
      BTserial.println(gps.satellites.value());

      // Horizontal Dim. of Precision (100ths-i32)
      BTserial.print("HDOP = ");
      BTserial.println(gps.hdop.value());

      sensorValue = analogRead(sensorPin);

      delay(20);
    }
  }
}
