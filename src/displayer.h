#ifndef DISPLAYER_H
#define DISPLAYER_H

#include "controller.h"

void welcomeUser(Controller*);
void displayMenu();
void stayOrQuit(Controller*);
void displaySat1();
void displaySat2();
void topNAgencies(Controller*, uint);
void topNCountries(Controller*, uint);
void orbitTypesAndPercentage(Controller*);
void purposesAndPercentage(Controller*);
void top1Country(Controller*);
void top1Agency(Controller*);
void topNRecentLaunchDate(Controller*, uint);
void topNOldestLaunchDate(Controller*, uint);
void newestSatellite(Controller*);
void oldestSatellite(Controller*);
void topNFastestRotationTime(Controller*, uint);
void topNSlowestRotationTime(Controller*, uint);
void topNHighestApogee(Controller*, uint);
void topNClosestPerigee(Controller*, uint);

#endif // DISPLAYER_H