#include "displayer.h"
#include "satellite.h"
#include "hashmap.h"
#include "controller.h"

void welcomeUser(Controller* this) {
    printf("    .          .     *  .                .        .\n");
    printf("      *   *   *   *   * WELCOME TO *   *   *   *   *\n");
    printf("  *    .        .    *             .         .      .   *\n");
    printf("       * .      .    _    .    _  _  _  _      .        .\n");
    printf("  *      ___   __ _ | |_  ___ | || |(_)| |_  ___      *\n");
    printf(".       / __| / _  || __|/ _ \\| || || || __|/ _ \\      .   *\n ");
    printf("       \\__ \\| (_| || |_|  __/| || || || |_|  __/        .\n");
    printf("  *     |___/ \\__,_| \\__|\\___||_||_||_| \\__|\\___|  .\n");
    printf("    .            .     .                 .           .    *\n");
    printf("    *      .      C A T E G O R I Z E R       .\n");
    printf(" .    .        .           *      .         .    *   .\n");
    printf("    .       *    .  *  .                 .       .      .\n");
    printf(" .   Let's explore Earth-orbiting satellites together!\n");
    printf("       .        .    .      *      .          .    *\n");

    stayOrQuit(this);
}

void displayMenu() {
    printf("\n* What interests you the most? Pick one of the options below *\n");
    printf("\n1. Display Top N agencies owning the highest number of satellites\n");
    printf("2. Display Top N countries with the highest number of satellites\n");
    printf("3. Explore types of orbits and their respective percentages\n");
    printf("4. Explore the purposes of Earth-orbiting satellites\n");
    printf("5. Identify the country with the highest number of satellites in Earth's orbit\n");
    printf("6. Identify the agency that owns the most satellites orbiting Earth\n");
    printf("7. Display Top N satellites based on the most recent launch date\n");
    printf("8. Display Top N satellites based on the oldest launch date\n");
    printf("9. Identify the oldest satellite currently in orbit\n");
    printf("10. Identify the newest satellite currently in orbit\n");
    printf("11. Display Top N satellites with the fastest rotation time\n");
    printf("12. Display Top N satellites with the slowest rotation time\n");
    printf("13. Display Top N satellites with the highest apogee (farthest point from Earth)\n");
    printf("14. Display Top N satellites with the closest perigee (nearest point to Earth)\n");
    printf("0. Exit *Satellite Categorizer*\n");
}

void stayOrQuit(Controller* this) {
    int choice;
    char buffer[256];

    do {
        printf("\n* Do you want to -> 1. Display menu or 2. Quit?\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input. Please enter a number.\n");
            fgets(buffer, sizeof(buffer), stdin);
            continue;
        }

        switch (choice) {
            case 1:
                displayMenu();
                break;
            case 2:
                exitProgram(this);
                break;
            default:
                printf("\nInvalid choice. Please enter 1 or 2.\n");
        }
    } while (choice != 1 && choice != 2);
}

void displaySat1() {
    printf("\n                }--O--{\n");
    printf("                  [^]\n");
    printf("                 /ooo\\\n");
    printf(" ______________:/o   o\\:______________\n");
    printf("|=|=|=|=|=|=|:A|\":|||:\"|A:|=|=|=|=|=|=|\n");
    printf("^\"\"\"\"\"\"\"\"\"\"\"\"\"\"!::{o}::!\"\"\"\"\"\"\"\"\"\"\"\"\"\"^\n");
    printf("                \\     /\n");
    printf("                 \\.../\n");
    printf("      ____       \"---\"       ____\n");
    printf("     |\\/\\/|=======|*|=======|\\/\\/|\n");
    printf("     :----\"       /-\\       \"----:\n");
    printf("                 /ooo\\\n");
    printf("                #|ooo|#\n");
    printf("                 \\___/\n");
    printf("\n");
}

void displaySat2() {
    printf("\n         ooo\n");
    printf("        / : \\\n");
    printf("       / o0o \\\n");
    printf(" _____\"~~~~~~~\"_____\n");
    printf(" \\+###|U * * U|###+/\n");
    printf("  \\...!(>...<)!.../\n");
    printf("   ^^^^o|   |o^^^^\n");
    printf("+=====}:^^^^^:{=====+#\n");
    printf(".____  .|!!!|.  ____.\n");
    printf("|#####:/\" \" \"\\:#####|\n");
    printf("|#####=|  O  |=#####|\n");
    printf("|#####>\\_____/<#####|\n");
    printf(" ^^^^^   | |   ^^^^^\n");
    printf("         o o\n");
    printf("\n");
}

void topNAgencies(Controller* this, uint n) {
    printf("*--------------------------------------------|----------------------*\n");
    printf("  %-42s | %-20s\n", "Agency", "Number of Satellites");
    printf("*--------------------------------------------|----------------------*\n");

    for (size_t i = this->agencies.size - 1; i >= this->agencies.size - n; --i) {
        uint agencyIndex = this->agencies.arr[i].second;
        uint numberOfSatellites = this->agencies.arr[i].first;
        const char* agency = getKey(this->agencyIndices, agencyIndex);

        printf("  %-42s | %-20u\n", agency, numberOfSatellites);
    }
    printf("*--------------------------------------------|----------------------*\n");

    stayOrQuit(this);
}

void topNCountries(Controller* this, uint n) {
    printf("*---------------------------|----------------------*\n");
    printf("  %-25s | %-20s\n", "Agency", "Number of Satellites");
    printf("*---------------------------|----------------------*\n");

    for (size_t i = this->countries.size - 1; i >= this->countries.size - n; --i) {
        uint countryIndex= this->countries.arr[i].second;
        uint numberOfSatellites = this->countries.arr[i].first;
        const char* country = getKey(this->countryIndices, countryIndex);

        printf("  %-25s | %-20u\n", country, numberOfSatellites);
    }
    printf("*---------------------------|----------------------*\n");

    stayOrQuit(this);
}

void orbitTypesAndPercentage(Controller* this) {
    printf("*---------------------------|----------------------*\n");
    printf("  %-25s | %-20s\n", "Orbit Type", "Percentage");
    printf("*---------------------------|----------------------*\n");

    for (size_t i = 0; i < this->orbitTypes.size; ++i) {
        uint orbitTypeIndex = this->orbitTypes.arr[i].second;
        const char* orbitType = getKey(this->orbitTypeIndices, orbitTypeIndex);
        float percentage = (float)this->orbitTypes.arr[i].first / (float)this->satellites.size;

        printf("  %-25s | %-19.2f%%\n", orbitType, percentage * 100);
    }
    printf("*---------------------------|----------------------*\n");
    printf("\n* LEO - Low Earth Orbit\n* MEO - Medium Earth Orbit\n*"
           " GEO - Geostationary Earth Orbit\n* HEO - Highly Elliptical Orbit\n");

    stayOrQuit(this);
}

void purposesAndPercentage(Controller* this) {
    printf("*-------------------------------------|----------------------*\n");
    printf("  %-35s | %-20s\n", "Purpose", "Percentage");
    printf("*-------------------------------------|----------------------*\n");

    for (size_t i = 0; i < this->purposes.size; ++i) {
        uint purposeIndex = this->purposes.arr[i].second;
        const char* purpose = getKey(this->purposeIndices, purposeIndex);
        float percentage = (float)this->purposes.arr[i].first / (float)this->satellites.size;

        printf("  %-35s | %-19.2f%%\n", purpose, percentage * 100);
    }
    printf("*-------------------------------------|----------------------*\n");

    stayOrQuit(this);
}

void top1Country(Controller* this) {
    displaySat1();
    topNCountries(this, 1);
}

void top1Agency(Controller* this) {
    displaySat2();
    topNAgencies(this, 1);
}

void topNRecentLaunchDate(Controller* this, uint n) {
    printf("*---------------------------|--------------*\n");
    printf("  %-25s | %-12s\n", "Satellite Name", "Launch Date");
    printf("*---------------------------|--------------*\n");

    for (size_t i = this->launchDates.size - 1; i >= this->launchDates.size - n; --i) {
        uint satelliteID = this->launchDates.arr[i]->id;
        const char* satelliteName = this->satellites.arr[satelliteID]->name;
        uint year = this->launchDates.arr[i]->year;
        uint month = this->launchDates.arr[i]->month;
        uint day = this->launchDates.arr[i]->day;

        printf("  %-25s |  %04u-%02u-%02u\n", satelliteName, year, month, day);
    }
    printf("*---------------------------|--------------*\n");

    stayOrQuit(this);
}

void topNOldestLaunchDate(Controller* this, uint n) {
    printf("*---------------------------|--------------*\n");
    printf("  %-25s | %-12s\n", "Satellite Name", "Launch Date");
    printf("*---------------------------|--------------*\n");

    for (size_t i = 0; i < n; ++i) {
        uint satelliteID = this->launchDates.arr[i]->id;
        const char* satelliteName = this->satellites.arr[satelliteID]->name;
        uint year = this->launchDates.arr[i]->year;
        uint month = this->launchDates.arr[i]->month;
        uint day = this->launchDates.arr[i]->day;

        printf("  %-25s |  %04u-%02u-%02u   \n", satelliteName, year, month, day);
    }
    printf("*---------------------------|--------------*\n");

    stayOrQuit(this);
}

void newestSatellite(Controller* this) {
    displaySat1();
    topNRecentLaunchDate(this, 1);
}

void oldestSatellite(Controller* this) {
    displaySat2();
    topNOldestLaunchDate(this, 1);
}

void topNFastestRotationTime(Controller* this, uint n) {
    printf("*---------------------------|---------------*\n");
    printf("  %-25s | %-12s \n", "Satellite Name", "Rotation time");
    printf("*---------------------------|---------------*\n");

    for (size_t i = 0; i < n; ++i) {
        uint satelliteID = this->rotTimes.arr[i].second;
        uint rotTime = this->rotTimes.arr[i].first;
        const char* satelliteName = this->satellites.arr[satelliteID]->name;

        printf("  %-25s | %4u mins\n", satelliteName, rotTime);
    }
    printf("*---------------------------|---------------*\n");

    stayOrQuit(this);
}

void topNSlowestRotationTime(Controller* this, uint n) {
    printf("*---------------------------|---------------*\n");
    printf("  %-25s | %-12s \n", "Satellite Name", "Rotation time");
    printf("*---------------------------|---------------*\n");

    for (size_t i = this->rotTimes.size - 1; i >= this->rotTimes.size - n; --i) {
        uint satelliteID = this->rotTimes.arr[i].second;
        uint rotTime = this->rotTimes.arr[i].first;
        const char* satelliteName = this->satellites.arr[satelliteID]->name;

        printf("  %-25s | %4u mins\n", satelliteName, rotTime);
    }
    printf("*---------------------------|---------------*\n");

    stayOrQuit(this);
}

void topNHighestApogee(Controller* this, uint n) {
    printf("*---------------------------|-------------*\n");
    printf("  %-25s | %-12s \n", "Satellite Name", "Apogee");
    printf("*---------------------------|-------------*\n");

    for (size_t i = this->apogees.size - 1; i >= this->apogees.size - n; --i) {
        uint satelliteID = this->apogees.arr[i].second;
        uint apogee = this->apogees.arr[i].first;
        const char* satelliteName = this->satellites.arr[satelliteID]->name;

        printf("  %-25s | %u\n", satelliteName, apogee);
    }
    printf("*---------------------------|-------------*\n");
    printf("\n* Apogee - The point in an orbit that is farthest from the Earth (or another celestial body).\n");

    stayOrQuit(this);
}

void topNClosestPerigee(Controller* this, uint n) {
    printf("*---------------------------|-------------*\n");
    printf("  %-25s | %-12s \n", "Satellite Name", "Perigee");
    printf("*---------------------------|-------------*\n");

    for (size_t i = 0; i < n; ++i) {
        uint satelliteID = this->perigees.arr[i].second;
        uint perigee = this->perigees.arr[i].first;
        const char* satelliteName = this->satellites.arr[satelliteID]->name;

        printf("  %-25s | %u\n", satelliteName, perigee);
    }
    printf("*---------------------------|-------------*\n");
    printf("\n* Perigee - The point in an orbit that is closest to the Earth (or another celestial body).\n");

    stayOrQuit(this);
}
