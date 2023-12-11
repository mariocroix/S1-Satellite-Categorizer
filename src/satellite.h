#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

typedef unsigned int uint;

typedef struct {
    uint year;
    uint month;
    uint day;
    uint id;
} Date;

Date* createDate(uint, uint, uint, uint);

typedef struct {
    uint id;
    char name[50];
    char purpose[50];
    char agency[50];
    char country[50];
    Date* launchDate;
    char orbitType[4];
    uint perigee;
    uint apogee;
    float rotTime;
} Satellite;

Satellite* createSatellite(uint, const char[], const char[], const char[], const char[], Date*, const char[], uint, uint, float);

typedef struct {
    uint first;
    uint second;
} Pair;

#endif // STRUCTS_H