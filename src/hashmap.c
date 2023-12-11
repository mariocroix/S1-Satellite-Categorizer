#include "hashmap.h"
#include "satellite.h"
#include "list.h"

Hashmap* createHashmap(size_t oldCap) {
    Hashmap* newMap = (Hashmap*)malloc(sizeof(Hashmap));
    newMap->size = 0;
    newMap->cap = nextPrime(oldCap);
    newMap->arr = (Node**)malloc(sizeof(Node*) * newMap->cap);

    if (newMap->arr == NULL) {
        free(newMap);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < newMap->cap; ++i) {
        Node* head = NULL;
        newMap->arr[i] = head;
    }

    return newMap;
}

bool isPrime(uint num) {
    if (num <= 1) {
        return false;
    }

    for (int i = 2; i <= num / 2; ++i) {
        if (num % i == 0) {
            return false;
        }
    }

    return true;
}

uint nextPrime(uint currPrime) {
    while (!isPrime(++currPrime));
    return currPrime;
}

uint hash(Hashmap* this, const char* key) {  // DJB2
    uint hash = 5381;
    int c;

    while (*key != '\0') {
        c = (int)*key;
        ++key;
        hash = ((hash << 5) + hash) ^ c;
    }

    return hash % this->cap;
}

bool contains(Hashmap* this, const char* key) {
    uint index = hash(this, key);

    Node* current = this->arr[index];
    while (current != NULL) {
        if (strcmp(current->pair.key, key) == 0) {
            return true;
        }
        current = current->next;
    }
    return false;
}

float getLoadFactor(Hashmap* this) {
    return (float)this->size / (float)this->cap;
}

void freeHashmap(Hashmap* this) {
    for (int i = 0; i < this->cap; ++i) {
        freeList(&this->arr[i]);
    }
}

void rehash(Hashmap** this) {
    Hashmap* oldMap = *this;

    Hashmap* newMap = createHashmap(oldMap->cap);

    for (int i = 0; i < oldMap->cap; ++i) {
        Node* current = oldMap->arr[i];
        while (current != NULL) {
            insert(&newMap, current->pair.key, current->pair.value);
            current = current->next;
        }
    }

    freeHashmap(oldMap);
    *this = newMap;
}

void insert(Hashmap** this, const char* key, uint value) {
    uint index = hash(*this, key);

    pushFront(&(*this)->arr[index], key, value);

    ++(*this)->size;

    if (getLoadFactor(*this) > 0.7) {
        rehash(&(*this));
    }
}

uint getValue(Hashmap* this, const char* key) {
    uint index = hash(this, key);

    Node* current = this->arr[index];
    while (current != NULL) {
        if (strcmp(current->pair.key, key) == 0) {
            return current->pair.value;
        }
        current = current->next;
    }
    return false;
}

const char* getKey(Hashmap* this, uint value) {
    for (int i = 0; i < this->cap; ++i) {
        Node* current = this->arr[i];
        while(current != NULL) {
            if (current->pair.value == value) {
                return current->pair.key;
            }
            current = current->next;
        }
    }
    return "NULL";
}



