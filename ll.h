#pragma once

struct node {

	char inp[100];
	unsigned char hash[5];
	struct node* next;

};


struct LinkedList {
	int size;	
	struct node* head; 
};



//Function prototypes

void initialize(struct LinkedList* list);

void addItem(struct LinkedList* list, char* cmd);

void printList(struct LinkedList* list);

unsigned char* hash(char* cmd, unsigned char* nodehash);

void revList(struct LinkedList* list);