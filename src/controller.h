#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "vector.h"
#include "hashmap.h"

typedef struct {
    uint numberOfQueries;
    Container satellites;
    Vector purposes;
    Vector agencies;
    Vector countries;
    Vector orbitTypes;
    Dates launchDates;
    Vector perigees;
    Vector apogees;
    Vector rotTimes;
    Hashmap* purposeIndices;
    Hashmap* agencyIndices;
    Hashmap* countryIndices;
    Hashmap* orbitTypeIndices;
} Controller;

void run(Controller* this, const char*);
void createController(Controller*);
void parse(Controller*, const char*);

void readQueryChoice(Controller*);
void callQuery(Controller*, uint);
uint readQueryN(size_t);
void freeController(Controller*);
void exitProgram(Controller*);
void toVectors(Controller*, Satellite*);
void toPurposes(Controller*, const char*);
void toAgencies(Controller*, const char*);
void toCountries(Controller*, const char*);
void toLaunchDates(Controller*, Date*);
void toOrbitTypes(Controller*, const char*);
void toPerigees(Controller*, uint, uint);
void toApogees(Controller*, uint, uint);
void toRotTimes(Controller*, float, uint);
void sortVectors(Controller*);

#endif // CONTROLLER_H