#ifndef HASHMAP_H
#define HASHMAP_H

#include "satellite.h"
#include "list.h"

typedef struct {
    Node** arr;
    size_t size;
    size_t cap;
} Hashmap;

Hashmap* createHashmap(size_t);
uint nextPrime(uint);
bool isPrime(uint);
uint hash(Hashmap*, const char*);
bool contains(Hashmap*, const char*);
float getLoadFactor(Hashmap*);
void freeHashmap(Hashmap*);
void rehash(Hashmap**);
void insert(Hashmap**, const char*, uint);
uint getValue(Hashmap*, const char*);
const char* getKey(Hashmap*, uint);

#endif // HASHMAP_H