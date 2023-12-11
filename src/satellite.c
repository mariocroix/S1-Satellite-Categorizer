#include "satellite.h"

Date* createDate(uint day, uint month, uint year, uint id) {
    Date* launchDate = (Date*)malloc(sizeof(Date));
    launchDate->day = day;
    launchDate->month = month;
    launchDate->year = year;
    launchDate->id = id;

    return launchDate;
}

Satellite* createSatellite(uint id, const char name[], const char purpose[], const char agency[], const char country[],
                     Date* launchDate, const char orbitType[], uint perigee, uint apogee, float rotTime) {
    Satellite* satellite = (Satellite*)malloc(sizeof(Satellite));
    satellite->id = id;
    strcpy(satellite->name, name);
    strcpy(satellite->purpose, purpose);
    strcpy(satellite->agency, agency);
    strcpy(satellite->country, country);
    satellite->launchDate = launchDate;
    strcpy(satellite->orbitType, orbitType);
    satellite->perigee = perigee;
    satellite->apogee = apogee;
    satellite->rotTime = rotTime;

    return satellite;
}
