#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxInp 256
#define hashSize 5			//	bc 40 bits

typedef struct Node {
	char cmd[maxInp];
	unsigned char hash[hashSize];
	struct Node* next;
} Node;

//		glonal pointers
extern Node* head;
extern Node* tail;

//		hash stuff
void computeHash(char* inp, unsigned char* prev, unsigned char* out[hashSize]);
void printHash(unsigned char* hash);
int compareHash(unsigned char* h1, unsigned char* h2);

//linked list functions
void addHistory(char* cmd);
void printHistory();
void validateHistory();
