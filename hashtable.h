#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <stdbool.h>

enum HashTableType {
	INT_T,
	ANY_T
};

typedef struct HashEntry {
	unsigned long full_hash;
	bool taken;
	void* value;
} HashEntry;

typedef struct HashTable {
	enum HashTableType type;
	size_t size;
	HashEntry* entries;
} HashTable;

bool hashtable_set_int(HashTable* hashtable, char* key, int value);

bool hashtable_set(HashTable* hashtable, char* key, void* value);

bool hashtable_get_int(HashTable* hashtable, int* buffer, char* key);

bool hashtable_get(HashTable* hashtable, HashEntry* buffer, char* key);

HashTable* hashtable_new(enum HashTableType type, size_t size);

void hashtable_free(HashTable* hashtable);

#endif // _HASHTABLE_H
