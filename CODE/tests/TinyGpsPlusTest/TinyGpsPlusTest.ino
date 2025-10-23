#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

static const int RXPin = 4, RXPin = 3;
static const uint32_t GPSBaud = 4800;

TinyGPSPlus gps;

SoftwareSerial serialS(RXPin, TXPin); // Gebruik geen TX en RX pin, emulate TX en RX via software

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ss.begin(GPSBaud);
}

void loop() {
  // put your main code here, to run repeatedly:
  int satellieten = gps.satellites.value();
  float latitude = gps.location.lat(); 
  float longitude = gps.location.lng();

  float precision = gps.hdop.hdop(); // precisie van de locatie (lon, lat)  
  //minder dan 2 is goed, hoger is slechte ontvangst
  float altitude = gps.altitude.meters();

  float heading = gps.course.deg();
  float speed = gps.speed.kmph();

}
