#include "list.h"

Node* createNode(const char* key, uint value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Error allocating memory for a new Node.\n");
        exit(EXIT_FAILURE);
    }

    newNode->pair.value = value;
    newNode->pair.key = key;
    newNode->next = NULL;

    return newNode;
}

void pushFront(Node** head, const char* key, uint value) {
    Node* newNode = createNode(key, value);
    newNode->next = *head;
    *head = newNode;
}

void freeList(Node** head) {
    Node* current = *head;
    Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}
