#include "TCXWriter.hpp"

#define RADIUS_EARTH_M 6371000.0
TCXWriter::TCXWriter() 
{
}

double toRadians(double degree) {
    return degree * (M_PI / 180.0);
}

double distance(double lat1, double lon1, double lat2, double lon2) {
    double dlat = toRadians(lat2 - lat1);
    double dlon = toRadians(lon2 - lon1);

    double a = sin(dlat / 2.0) * sin(dlat / 2.0) + cos(toRadians(lat1)) * cos(toRadians(lat2)) * sin(dlon / 2.0) * sin(dlon / 2.0);
    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));

    return RADIUS_EARTH_M * c;
}

void TCXWriter::begin(const char* filename) 
{
    if(!SD.begin()){ //CS pin nog specificeren
        Serial.println("SD card initialization failed!");
        return;
    }
    
    tcxFile = SD.open(filename, FILE_WRITE);
    if(tcxFile) {
        tcxFile.println(F("<?xml version=\"1.0\" encoding=\"UTF-8\"?>"));
        tcxFile.println(F("<TrainingCenterDatabase"));
        tcxFile.println(F("  xsi:schemaLocation=\"http://www.garmin.com/xmlschemas/TrainingCenterDatabase/v2 http://www.garmin.com/xmlschemas/TrainingCenterDatabasev2.xsd\""));
        tcxFile.println(F("  xmlns:ns5=\"http://www.garmin.com/xmlschemas/ActivityGoals/v1\""));
        tcxFile.println(F("  xmlns:ns3=\"http://www.garmin.com/xmlschemas/ActivityExtension/v2\""));
        tcxFile.println(F("  xmlns:ns2=\"http://www.garmin.com/xmlschemas/UserProfile/v2\""));
        tcxFile.println(F("  xmlns=\"http://www.garmin.com/xmlschemas/TrainingCenterDatabase/v2\""));
        tcxFile.println(F("  xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:ns4=\"http://www.garmin.com/xmlschemas/ProfileExtension/v1\">"));
        tcxFile.println(F("  <Activities>"));
        tcxFile.println(F("    <Activity Sport=\"Biking\">"));


        lapDistance = 0.0;
        totalDistance = 0.0;
        lapTime = 0;
        lapDistanceFlag = false;
    } else {
        Serial.println("Error opening file for writing");
    }
}

void TCXWriter::writeHeader(int year, int month, int day, int hour, int min, int sec){
    if(tcxFile){
        char tcxtime[21];
        generateTCXTime(year, month, day, hour, min, sec, tcxtime);
        tcxFile.print(F("      <Id>"));
        tcxFile.print(tcxtime);
        tcxFile.println(F("</Id>"));
        writeLap(year, month, day, hour, min, sec);
    } else {
        Serial.println("File not open");
    }
}

void TCXWriter::writeFooter(){
    if(tcxFile){
        closeLap();
        tcxFile.println(F("    </Activity>"));
        tcxFile.println(F("  </Activities>"));
        tcxFile.println(F("</TrainingCenterDatabase>"));
        tcxFile.close();
    } else {
        Serial.println("File not open");
    }
}

void TCXWriter::addTrackpoint(float lat, float lon, float alt, int hr, int year, int month, int day, int hour, int min, int sec, int cad, int pw, int spd){
    if(tcxFile){
        char tcxtime[21];
        generateTCXTime(year, month, day, hour, min, sec, tcxtime);
        tcxFile.println(F("        <Trackpoint>"));
        tcxFile.print(F("          <Time>"));
        tcxFile.print(tcxtime);
        tcxFile.println(F("</Time>"));
        tcxFile.println(F("          <Position>"));
        tcxFile.print(F("            <LatitudeDegrees>"));
        tcxFile.print(lat, 6);
        tcxFile.println(F("</LatitudeDegrees>"));
        tcxFile.print(F("            <LongitudeDegrees>"));
        tcxFile.print(lon, 6);
        tcxFile.println(F("</LongitudeDegrees>"));
        tcxFile.println(F("          </Position>"));
        tcxFile.print(F("          <AltitudeMeters>"));
        tcxFile.print(alt, 1);
        tcxFile.println(F("</AltitudeMeters>"));
        tcxFile.print(F("          <DistanceMeters>"));
        
        if(lapDistanceFlag){
            float dist = distance(currentLat, currentLon, lat, lon);
            lapDistance += dist;
            totalDistance += dist;
            tcxFile.print(totalDistance);
        } else {
            currentLat = lat;
            currentLon = lon;
            lapDistanceFlag = true;
            tcxFile.print(totalDistance);
        }
        
        tcxFile.println(F("</DistanceMeters>"));
        tcxFile.println(F("          <HeartRateBpm>"));
        tcxFile.print(F("            <Value>"));
        tcxFile.print(hr);
        tcxFile.println(F("</Value>"));
        tcxFile.println(F("          </HeartRateBpm>"));
        if(cad != -1){
            tcxFile.print(F("          <Cadence>"));
            tcxFile.print(cad);
            tcxFile.println(F("</Cadence>"));
        }
        if(spd != -1){
            tcxFile.println(F("          <Extensions>"));
            tcxFile.println(F("            <ns3:TPX>"));
            tcxFile.print(F("              <ns3:Speed>"));
            tcxFile.print(spd / 3.6, 1); //convert km/h to m/s
            tcxFile.println(F("</ns3:Speed>"));
            if(pw != -1){
                tcxFile.print(F("              <ns3:Watts>"));
                tcxFile.print(pw);
                tcxFile.println(F("</ns3:Watts>"));
            }
            tcxFile.println(F("            </ns3:TPX>"));
            tcxFile.println(F("          </Extensions>"));
        }
        tcxFile.println(F("        </Trackpoint>"));
    } else {
        Serial.println("File not open");
    }
}

void TCXWriter::startNewLap(int year, int month, int day, int hour, int min, int sec) {
    if(tcxFile){
        closeLap();
        writeLap(year, month, day, hour, min, sec);
    } else {
        Serial.println("File not open");
    }
}

void TCXWriter::generateTCXTime (int year, int month, int day, int hour, int min, int sec, char *tcxtime)
{
  snprintf(tcxtime, 21, "%04d-%02d-%02dT%02d:%02d:%02dZ", year, month, day, hour, min, sec);
}


void TCXWriter::writeLap(int year, int month, int day, int hour, int min, int sec) {
    if(tcxFile){
        tcxFile.print(F("      <Lap StartTime=\""));
        char tcxtime[21];
        generateTCXTime(year, month, day, hour, min, sec, tcxtime); 
        tcxFile.print(tcxtime);
        tcxFile.println(F("\">"));
        tcxFile.println(F("        <Track>"));
        
        lapDistance = 0.0;
        lapTime = millis() / 1000; //in seconds
    } else {
        Serial.println("File not open");
    }
}

void TCXWriter::closeLap() {
    if(tcxFile){
        lapTime = (millis() / 1000) - lapTime; //in seconds
        tcxFile.println(F("        </Track>"));
        tcxFile.print(F("        <TotalTimeSeconds>"));
        tcxFile.print(lapTime);
        tcxFile.println(F("</TotalTimeSeconds>"));
        tcxFile.print(F("        <DistanceMeters>"));
        tcxFile.print(lapDistance);
        tcxFile.println(F("</DistanceMeters>"));
        tcxFile.println(F("      </Lap>"));
        
        lapDistanceFlag = false;
    } else {
        Serial.println("File not open");
    }
}