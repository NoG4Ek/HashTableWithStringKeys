#include "HashTable.h"


hashIndexType hash(keyType key) {
	unsigned char Rand8[256];

	hashIndexType h;
	unsigned char h1, h2;

	if (*key == 0) return 0;
	h1 = *key; h2 = *key + 1;
	key++;
	while (*key) {
		h1 = h1 ^ *key;
		h2 = h2 ^ *key;
		key++;
	}

	/* h is in range 0..65535 */
	h = ((hashIndexType)h1 << 8) | (hashIndexType)h2;
	/* use division method to scale */
	return h % hashTableSize;
}

statusEnum insert(keyType key, recType *rec) {
	nodeType *p, *p0;
	hashIndexType bucket;

	 /* Insert node at beginning of list */
	bucket = hash(key);
	if ((p = malloc(sizeof(nodeType))) == 0)
		return STATUS_MEM_EXHAUSTED;
	p0 = hashTable[bucket];
	hashTable[bucket] = p;
	p->next = p0;
	p->key = key;
	p->rec = *rec;
	return STATUS_OK;
}

statusEnum delete(keyType key) {
	nodeType *p0, *p;
	hashIndexType bucket;

	 /* Find node */
	p0 = 0;
	bucket = hash(key);
	p = hashTable[bucket];
	while (p && !compEQ(p->key, key)) {
		p0 = p;
		p = p->next;
	}
	if (!p) return STATUS_KEY_NOT_FOUND;

	/* p designates node to delete, remove it from list */
	if (p0)
		/* Not first node, p0 points to previous node */
		p0->next = p->next;
	else
		/* First node on chain */
		hashTable[bucket] = p->next;

	free(p);
	return STATUS_OK;
}

statusEnum find(keyType key, recType *rec) {
	nodeType *p;
	hashIndexType bucket = hash(key);
	p = hashTable[bucket];
	while (p && !compEQ(p->key, key))
		p = p->next;
	if (!p) return STATUS_KEY_NOT_FOUND;
	*rec = p->rec;
	return STATUS_OK;
}

void clearMem() {
	free(hashTable);
}