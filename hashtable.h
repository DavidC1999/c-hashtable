#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <stdbool.h>

typedef struct HashEntry {
	unsigned long full_hash;
	bool taken;
	int value;
} HashEntry;

typedef struct HashTable {
	size_t size;
	HashEntry* entries;
} HashTable;

bool hashtable_set(HashTable* hashtable, char* key, int value);

bool hashtable_get(HashTable* hashtable, int* buffer, char* key);

HashTable* hashtable_new(size_t size);

void hashtable_free(HashTable* hashtable);

bool hashtable_clear(HashTable* hashtable, char* key);

#endif // _HASHTABLE_H
