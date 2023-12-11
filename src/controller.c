#include "controller.h"
#include "satellite.h"
#include "hashmap.h"
#include "vector.h"
#include "displayer.h"

#define INITIAL_NUMBER_OF_QUERIES 14
#define INITIAL_CAP_OF_HASHMAP 5

void run(Controller* this, const char* fileName) {
    createController(this);
    parse(this, fileName);
    sortVectors(this);
    welcomeUser(this);
    readQueryChoice(this);
}

void createController(Controller* this) {
    this->numberOfQueries = INITIAL_NUMBER_OF_QUERIES;
    createContainer(&this->satellites);
    createVector(&this->purposes);
    createVector(&this->agencies);
    createVector(&this->countries);
    createVector(&this->orbitTypes);
    createDates(&this->launchDates);
    createVector(&this->perigees);
    createVector(&this->apogees);
    createVector(&this->rotTimes);

    const int mapInitialCap = INITIAL_CAP_OF_HASHMAP;
    this->purposeIndices = createHashmap(mapInitialCap);
    this->agencyIndices = createHashmap(mapInitialCap);
    this->countryIndices = createHashmap(mapInitialCap);
    this->orbitTypeIndices = createHashmap(mapInitialCap);
}

void parse(Controller* this, const char* fileName) {
    FILE* file = fopen(fileName, "r");

    if (file == NULL) {
        fprintf(stderr, "Error opening the file.\n");
        exit(EXIT_FAILURE);
    }

    char header[256];
    fgets(header, sizeof(header), file);

    char name[50];
    char purpose[50];
    char agency[50];
    char country[50];
    uint day;
    uint month;
    uint year;
    char orbitType[4];
    uint perigee;
    uint apogee;
    float rotTime;

    uint numberOfSatellites = 0;
    createContainer(&this->satellites);

    do {
        fscanf(file, "%49[^,],%49[^,],%49[^,],%49[^,],%d/%d/%d,%3[^,],%d,%d,%f,\n",
               name, purpose, agency, country, &day, &month, &year, orbitType, &perigee, &apogee, &rotTime);

        Date* launchDate = createDate(day, month, year, numberOfSatellites);
        Satellite* satellite = createSatellite(numberOfSatellites, name, purpose, agency, country,
                                               launchDate, orbitType, perigee, apogee, rotTime);

        add(&this->satellites, satellite);
        toVectors(this, satellite);

        ++numberOfSatellites;

    } while (!feof(file));
}

void readQueryChoice(Controller* this) {
    int choice;
    char buffer[256];

    do {
        printf("\n* Enter your choice (0-%u) -> ", this->numberOfQueries);

        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input. Please enter a number.\n");

            fgets(buffer, sizeof(buffer), stdin);
            continue;
        }

        if (choice < 0 || choice > 14) {
            printf("\nInvalid choice. Please enter a number between 0 and %u.\n", this->numberOfQueries);
            continue;
        }

        callQuery(this, choice);

    } while (1);
}

uint readQueryN(size_t size) {
    uint n;
    char buffer[256];

    do {
        printf("\n* Enter N (should be less than or equal to %zu) -> ", size);
        if (scanf("%u", &n) != 1) {
            printf("\nInvalid input. Please enter a number.\n");

            fgets(buffer, sizeof(buffer), stdin);
            continue;
        }
        if (n <= 0 || n > size) {
            printf("\nInvalid choice. Please enter a number between 1 and %zu.\n", size);
            continue;
        }
        return n;
    } while (1);
}

void callQuery(Controller* this, uint queryNumber) {
    uint n;
    switch (queryNumber) {
        case 1:
            n = readQueryN(this->agencies.size - 1);
            topNAgencies(this, n);
            break;
        case 2:
            n = readQueryN(this->countries.size - 1);
            topNCountries(this, n);
            break;
        case 3:
            orbitTypesAndPercentage(this);
            break;
        case 4:
            purposesAndPercentage(this);
            break;
        case 5:
            top1Country(this);
            break;
        case 6:
            top1Agency(this);
            break;
        case 7:
            n = readQueryN(this->launchDates.size - 1);
            topNRecentLaunchDate(this, n);
            break;
        case 8:
            n = readQueryN(this->launchDates.size - 1);
            topNOldestLaunchDate(this, n);
            break;
        case 9:
            oldestSatellite(this);
            break;
        case 10:
            newestSatellite(this);
            break;
        case 11:
            n = readQueryN(this->rotTimes.size - 1);
            topNFastestRotationTime(this, n);
            break;
        case 12:
            n = readQueryN(this->rotTimes.size - 1);
            topNSlowestRotationTime(this, n);
            break;
        case 13:
            n = readQueryN(this->apogees.size - 1);
            topNHighestApogee(this, n);
            break;
        case 14:
            n = readQueryN(this->perigees.size - 1);
            topNClosestPerigee(this, n);
            break;
        case 0:
            exitProgram(this);
            break;
    }
}

void freeController(Controller* this) {
    free(this->orbitTypeIndices);
    free(this->countryIndices);
    free(this->agencyIndices);
    free(this->purposeIndices);
    freeVector(&this->rotTimes);
    freeVector(&this->apogees);
    freeVector(&this->perigees);
    freeDates(&this->launchDates);
    freeVector(&this->orbitTypes);
    freeVector(&this->countries);
    freeVector(&this->agencies);
    freeVector(&this->purposes);
    freeContainer(&this->satellites);
}

void exitProgram(Controller* this) {
    printf("\nExiting *Satellite Categorizer*. Goodbye!\n");
    freeController(this);
    exit(0);
}

void toVectors(Controller* this, Satellite* satellite) {
    toPurposes(this, satellite->purpose);
    toAgencies(this, satellite->agency);
    toCountries(this, satellite->country);
    toLaunchDates(this, satellite->launchDate);
    toOrbitTypes(this, satellite->orbitType);
    toPerigees(this, satellite->perigee, satellite->id);
    toApogees(this, satellite->apogee, satellite->id);
    toRotTimes(this, satellite->rotTime, satellite->id);
}

void toPurposes(Controller* this, const char* purpose) {
    if (contains(this->purposeIndices, purpose)) {
        uint index = getValue(this->purposeIndices, purpose);
        ++at(&this->purposes, index)->first;
    } else {
        uint index = size(&this->purposes);
        insert(&this->purposeIndices, purpose, index);
        pushBack(&this->purposes, (Pair){1, index});
    }
}

void toAgencies(Controller* this, const char* agency) {
    if (contains(this->agencyIndices, agency)) {
        uint index = getValue(this->agencyIndices, agency);
        ++at(&this->agencies, index)->first;
    } else {
        uint index = size(&this->agencies);
        insert(&this->agencyIndices, agency, index);
        pushBack(&this->agencies, (Pair){1, index});
    }
}

void toCountries(Controller* this, const char* country) {
    if (contains(this->countryIndices, country)) {
        uint index = getValue(this->countryIndices, country);
        ++at(&this->countries, index)->first;
    } else {
        uint index = size(&this->countries);
        insert(&this->countryIndices, country, index);
        pushBack(&this->countries, (Pair){1, index});
    }
}

void toLaunchDates(Controller* this, Date* launchDate) {
    addDate(&this->launchDates, launchDate);
}

void toOrbitTypes(Controller* this, const char* orbitType) {
    if (contains(this->orbitTypeIndices, orbitType)) {
        uint index = getValue(this->orbitTypeIndices, orbitType);
        ++at(&this->orbitTypes, index)->first;
    } else {
        size_t index = size(&this->orbitTypes);
        insert(&this->orbitTypeIndices, orbitType, index);
        pushBack(&this->orbitTypes, (Pair){1, index});
    }
}

void toPerigees(Controller* this, uint perigee, uint id) {
    pushBack(&this->perigees, (Pair){perigee, id});
}

void toApogees(Controller* this, uint apogee, uint id) {
    pushBack(&this->apogees, (Pair){apogee, id});
}

void toRotTimes(Controller* this, float rotTime, uint id) {
    pushBack(&this->rotTimes, (Pair){(int)rotTime, id});
}

void sortVectors(Controller* this) {
    sort(&this->purposes);
    sort(&this->agencies);
    sort(&this->countries);
    sort(&this->orbitTypes);
    sortDates(&this->launchDates);
    sort(&this->perigees);
    sort(&this->apogees);
    sort(&this->rotTimes);
}
