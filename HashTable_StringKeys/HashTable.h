#pragma once

#include <stdio.h>
#include <stdlib.h>

#define compEQ(a,b) (a == b)

/* Key's type */
typedef char *keyType;

/* User data stored in HT */
typedef struct {
	int stuff;
} recType;

/* Index into hash table */
typedef int hashIndexType;

/* Status list */
typedef enum {
	STATUS_OK,
	STATUS_MEM_EXHAUSTED,
	STATUS_KEY_NOT_FOUND
} statusEnum;

/* Node type */
typedef struct nodeTag {
	struct nodeTag *next;       /* next node */
	keyType key;                /* key */
	recType rec;                /* user data */
} nodeType;

nodeType **hashTable;
int hashTableSize;


/* Hash function applied to data */
hashIndexType hash(keyType key);

/* Allocate node for data and insert in table */
statusEnum insert(keyType key, recType *rec);

/* Delete node containing data from table */
statusEnum delete(keyType key);

/* Find node containing data */
statusEnum find(keyType key, recType *rec);

void clearMem();