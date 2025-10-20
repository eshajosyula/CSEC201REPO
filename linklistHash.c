#include "linklistHash.h"

//		global vars
Node* head = NULL;
Node* tail = NULL;


static void computeHash(const char* inp, const unsigned char* prev, unsigned char out[hashSize]) {
	int len;
	int i;

	if (inp == NULL) {
		len = 0;
	}
	else {
		len = (int)strlen(inp);
	}

	if (len == 0) {
		for (i = 0; i < 5; i++) {
			out[i] = 0;
		}
		return;
	}

	for (i = 0; i < 5; i++) {
		unsigned char ch;
		unsigned char ph;
		unsigned char x;

		ch = (unsigned char)inp[i % len];

		if (prev == NULL) {
			ph = 0xAA;
		}
		else {
			ph = prev[i % 5];
		}

		x = (unsigned char)(ch ^ ph);             // xor
		x = (unsigned char)((x & 0xF0) | ((~x) & 0x0F));		// and or not
		x = (unsigned char)((x << 1) | (x >> 7));     //	rotate 4 destruction
		x = (unsigned char)(x ^ (ph >> 2));           //		xor again
		out[i] = x;
	}
}

void printHash(const unsigned char* h) {
	int i;
	if (h == NULL) return;
	for (i = 0; i < hashSize; i++) {
		printf("%02x", h[i]);
	}
}

int compareHash(const unsigned char* h1, const unsigned char* h2) {
	int i;
	if (h1 == NULL && h2 == NULL) return 1;
	if (h1 == NULL || h2 == NULL) return 0;
	for (i = 0; i < hashSize; i++) {
		if (h1[i] != h2[i]) {
			return 0;
		}
	}
	return 1;
}


//	linkedlist/blockchain logic
void addHistory(char* cmd) {
	Node* newNode;
	unsigned char prev[hashSize];
	int i;

	if (cmd == NULL) return;
	if (*cmd == '\0') return;

	newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) {
		perror("malloc");
		exit(1);
	}

	strncpy(newNode->cmd, cmd, maxInp - 1);
	newNode->cmd[maxInp - 1] = '\0';
	newNode->next = NULL;

	//	 prev = tail->hash (or zeros if list empty) 
	if (tail == NULL) {
		for (i = 0; i < hashSize; i++) prev[i] = 0;
	}
	else {
		for (i = 0; i < hashSize; i++) prev[i] = tail->hash[i];
	}

	computeHash(newNode->cmd, prev, newNode->hash);

	//		append
	if (tail == NULL) {
		head = newNode;
		tail = newNode;
	}
	else {
		tail->next = newNode;
		tail = newNode;
	}
}

void printHistory(void) {
	Node* curr;
	int index;

	curr = head;
	index = 1;

	while (curr != NULL) {
		printf("%d: %s | Hash: ", index, curr->cmd);
		printHash(curr->hash);
		printf("\n");
		index = index + 1;
		curr = curr->next;
	}
}


//		validate the integrity of the chain
void validateHistory(void) {
	Node* curr;
	Node* nxt;
	int nodeNum;
	int i;

	curr = head;
	nodeNum = 1;

	while (curr != NULL && curr->next != NULL) {
		unsigned char recomputed[hashSize];

		nxt = curr->next;
		computeHash(nxt->cmd, curr->hash, recomputed);

		for (i = 0; i < hashSize; i++) {
			if (recomputed[i] != nxt->hash[i]) {
				printf("WARNING: Alteration detected at node #%d: %s\n", nodeNum + 1, nxt->cmd);
				return;
			}
		}

		curr = nxt;
		nodeNum = nodeNum + 1;
	}

	printf("Action Successful: History integrity validated. No alterations detected.\n");
}
