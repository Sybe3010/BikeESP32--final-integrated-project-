#include "gps.hpp"

GPS::GPS() {} // definieer constructor

void GPS::begin(unsigned long baud)
{
    // gebruik de meegegeven baud-parameter
    Serial2.begin(baud, SERIAL_8N1, GPS_SERIAL_RX_PIN, GPS_SERIAL_TX_PIN);
}

GPS::GPSData GPS::getAllData(){
    while (Serial2.available() > 0) {
        // cast naar char om signature overeen te laten komen
        gps.encode((char)Serial2.read());
    }
    GPSData data;
    
    data.latitude = gps.location.lat();
    data.longitude = gps.location.lng();
    data.speed = gps.speed.kmph();
    data.heading = gps.course.deg();
    data.altitude = gps.altitude.meters();
    data.precisionH = gps.hdop.hdop();
    data.satellites = gps.satellites.value();

    return data;
}
