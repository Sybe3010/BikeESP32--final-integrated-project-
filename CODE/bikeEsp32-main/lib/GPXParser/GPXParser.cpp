#include "GPXParser.hpp"

static std::vector<GPXTrackpoint> trackPoints;

GPXParser::GPXParser() 
{
}

void GPXParser::addTrackpoint(float lat, float lon, float ele) 
{
    GPXTrackpoint tp;
    tp.latitude = lat;
    tp.longitude = lon;
    tp.elevation = ele;
    trackPoints.push_back(tp);
}

void GPXParser::clearTrackpoints() 
{
    trackPoints.clear();
}

const std::vector<GPXTrackpoint>& GPXParser::getTrackPoints() 
{
    return trackPoints;
}

void GPXParser::parseFile(const char* filename){
    clearTrackpoints();
    File gpxFile = SD.open(filename);
    if(!gpxFile) {
        Serial.println("Error opening GPX file");
        return;
    }

    char line[256];
    float lat = 0.0, lon = 0.0, ele = 0.0;
    bool inTrkpt = false;

     while (gpxFile.available()) {
            size_t len = gpxFile.readBytesUntil('\n', line, sizeof(line) - 1);
            line[len] = '\0';

            // Zoek een trkpt regel
            if (strstr(line, "<trkpt")) {
                if (sscanf(line, " <trkpt lat=\"%f\" lon=\"%f\">", &lat, &lon) == 2) {
                    inTrkpt = true;
                    ele = 0;
                }
            }

            // Zoek elevation
            if (inTrkpt && strstr(line, "<ele>")) {
                sscanf(line, " <ele>%f</ele>", &ele);
            }

            // Einde trkpt
            if (strstr(line, "</trkpt>")) {
                addTrackpoint(lat, lon, ele);
                inTrkpt = false;
            }
        }

        gpxFile.close();
        return;
}