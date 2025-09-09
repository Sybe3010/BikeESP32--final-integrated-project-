#ifndef GPXPARSER_HPP
#define GPXPARSER_HPP

#include <Arduino.h>
#include <SD.h> //SPI connectie
#include <vector>
#include <string>

struct GPXTrackpoint {
    float latitude;
    float longitude;
    float elevation; // in meters
};

class GPXParser
{
    private:
        void addTrackpoint(float lat, float lon, float ele);
        void clearTrackpoints();
    public:
        const std::vector<GPXTrackpoint>& getTrackPoints();
        void parseFile(const char* filename);
        GPXParser();
};

#endif