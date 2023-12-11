#ifndef VECTOR_H
#define VECTOR_H

#include "satellite.h"

typedef struct {
    Pair* arr;
    size_t size;
    size_t cap;
} Vector;

void createVector(Vector*);
void freeVector(Vector*);
Pair* at(Vector*, size_t);
size_t size(Vector*);
void pushBack(Vector*, Pair);
void sort(Vector*);
void swap(Pair*, Pair*);
int partition(Vector*, int, int);
void quickSort(Vector*, int, int);

typedef struct {
    Satellite** arr;
    size_t size;
    size_t cap;
} Container;

void createContainer(Container*);
void freeContainer(Container*);
void add(Container*, Satellite*);

typedef struct {
    Date** arr;
    size_t size;
    size_t cap;
} Dates;

void createDates(Dates*);
void freeDates(Dates*);
void addDate(Dates*, Date*);
void sortDates(Dates*);
void swapDates(Date*, Date*);
int compareDates(Date*, Date*);
int partitionDates(Dates*, int, int);
void quickSortDates(Dates*, int, int);

#endif // VECTOR_H