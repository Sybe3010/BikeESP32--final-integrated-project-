#pragma once

#include <Arduino.h>
#include <TinyGPSPlus.h>

#define GPS_SERIAL_RX_PIN 17
#define GPS_SERIAL_TX_PIN 18


class GPS
{
    private:
        TinyGPSPlus gps;
    public:
        struct GPSData
        {
            double latitude;
            double longitude;
            double speed; // in km/h
            double heading; // in degrees
            double altitude; // in meters

            float precisionH; // HDOP: horizontal precision
            uint8_t satellites;
        };

        GPS();
        void begin(unsigned long baud);
        GPSData getAllData();   
};
