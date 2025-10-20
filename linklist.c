#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ll.h"

// REMOVE FROM BUILD

void initialize(struct LinkedList* list) {
    if (list == NULL) {
        return;
    }
    list->size = 0;
    list->head = NULL;
}


void addItem(struct LinkedList* list, char* cmd) {
    struct node* n;

    if (list == NULL) {
        return;
    }
    if (cmd == NULL) {
        return;
    }
    if (*cmd == '\0') {
        return;
    }

    n = (struct node*)malloc(sizeof(struct node));
    if (n == NULL) {
        perror("malloc");
        exit(1);
    }

    strncpy(n->inp, cmd, sizeof(n->inp) - 1);
    n->inp[sizeof(n->inp) - 1] = '\0';


    n->next = list->head;       // link new node 2 old head

    if (n->next != NULL) {        // compute hash based on next node if it exists 
        computeHash(n->next->inp, n->next->hash, n->hash);
    }
    else {
        computeHash("", NULL, n->hash);
    }

    list->head = n;
    list->size = list->size + 1;
}

void printList(struct LinkedList* list) {
    struct node* cur;
    int i;

    if (list == NULL) {
        return;
    }

    cur = list->head;
    i = 1;

    while (cur != NULL) {
        printf("%d: %s\n", i, cur->inp);
        i = i + 1;
        cur = cur->next;
    }
}


unsigned char* hash(char* cmd, unsigned char* nodehash) {
    static unsigned char out[5];
    computeHash(cmd, nodehash, out);
    return out;
}

void revList(struct LinkedList* list) {
    struct node* prev;
    struct node* cur;
    struct node* next;

    if (list == NULL) {
        return;
    }
    if (list->head == NULL) {
        return;
    }

    prev = NULL;
    cur = list->head;

    while (cur != NULL) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    list->head = prev;
}