#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "HashTable.h"


int main(int argc, char **argv) {
	char *inputF = argv[1];
	char *output_file = argv[2];
	
	int i, maxnum = 1000;
	hashTableSize = 2048;
	int x = 0;
	int type = 0;
	recType *rec;
	keyType *key;
	statusEnum err;

	if ((rec = malloc(maxnum * sizeof(recType))) == 0) {
		fprintf(stderr, "out of memory (rec)\n");
		exit(1);
	}
	if ((key = malloc(maxnum * sizeof(keyType))) == 0) {
		fprintf(stderr, "out of memory (key)\n");
		exit(1);
	}

	if ((hashTable = calloc(hashTableSize, sizeof(nodeType *))) == 0) {
		fprintf(stderr, "out of memory (hashTable)\n");
		exit(1);
	}

	FILE *fout = fopen(output_file, "w");
	FILE *fin = fopen(inputF, "r");
	
	char rkey[] = "asd";
	int ch = 0;
	x = fscanf(fin, "%u %s %u\n", &type, rkey, &rec[ch]);
	
	key[ch] = rkey;
	while (x == 3) {
		fprintf(fout, "%u %s %u\n", type, key[ch], rec[ch]);
		if (type == 0) {
			err = insert(key[ch], &rec[ch]);
			if (err) fprintf(fout, "insertERR, key=%s\n", key[ch]);
		}
		if (type == 1) {
			err = delete(key[ch]);
			if (err) fprintf(fout, "deleteERR, key=%s\n", key[ch]);
		}
		if (type == 2) {
			err = find(key[ch], &rec[ch]);
			if (err) fprintf(fout, "findERR, key=%s\n", key[ch]);
		}
		ch++;
		x = fscanf(fin, "%u %s %u\n", &type, rkey, &rec[ch]);
		key[ch] = rkey;
	}
	fclose(fin);

	fclose(fout);
	return 0;
}