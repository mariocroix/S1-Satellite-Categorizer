#ifndef LIST_H
#define LIST_H

#include "satellite.h"

typedef struct {
    const char* key;
    uint value;
} keyValue;

struct Node {
    struct Node* next;
    keyValue pair;
};

typedef struct Node Node;

Node* createNode(const char*, uint);
void pushFront(Node**, const char*, uint);
void freeList(Node**);

#endif // LIST_H
