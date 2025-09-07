#ifndef TCXWRITER_HPP
#define TCXWRITER_HPP

#include <Arduino.h>

#include <SD.h> //SPI connectie

class TCXWriter 
{
    public:
        TCXWriter();

        void begin(const char* filename);
        void writeHeader(int year, int month, int day, int hour, int min, int sec);
        void writeFooter();
        //latitude, longitude, altitude, heartrate, year, month, day, hour, minute, second, cadence, power, speed
        void addTrackpoint(float lat, float lon, float alt, int hr, int year, int month, int day, int hour, int min, int sec, int cad, int pw, int spd);
        void startNewLap(int year, int month, int day, int hour, int min, int sec);


        float lapDistance = 0.0; //in meters
        float totalDistance = 0.0; //in meters
        unsigned long lapTime; //in seconds
    private:
        File tcxFile;
        float currentLon;
        float currentLat;
        bool lapDistanceFlag;

        void generateTCXTime(int year, int month, int day, int hour, int min, int sec, char *tcxtime);
        void writeLap(int year, int month, int day, int hour, int min, int sec);
        void closeLap();
};

#endif // TCXWRITER_HPP