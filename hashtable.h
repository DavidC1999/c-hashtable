#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <stdbool.h>

enum HashTableType {
	INT_T,
	ANY_T
};

typedef struct HashEntry {
	bool taken;
	char* key;
	void* value;
} HashEntry;

typedef struct HashTable {
	enum HashTableType type;
	size_t size;
	bool free_entry_values;
	HashEntry* entries;
} HashTable;

// specific set method for int
// handles type checking
bool hashtable_set_int(HashTable* hashtable, char* key, int value);

// general set method
// type-unsafe
bool hashtable_set(HashTable* hashtable, char* key, void* value);

// specific get method for int
// handles type checking
bool hashtable_get_int(HashTable* hashtable, int* buffer, char* key);

// general get method
// type-unsafe
bool hashtable_get(HashTable* hashtable, HashEntry* buffer, char* key);

// mallocs a new hashtable with initial values
HashTable* hashtable_new(enum HashTableType type, size_t size);

// override default setting
// frees the void* value from all HashEntries in the HashTable on
// a call to hashtable_free
void hashtable_force_free_values(HashTable* hashtable);

// frees the hashtable
void hashtable_free(HashTable* hashtable);

#endif // _HASHTABLE_H
