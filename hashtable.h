#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct HashEntry {
    char* key;
    void* value;
} HashEntry;

typedef struct HashTable {
    size_t size;
    HashEntry* entries;
} HashTable;

// sets a key to a certain value
// returns: success or not
bool hashtable_set(HashTable* hashtable, char* key, void* value);

// gets the value associated with a key
// returns: success or not
bool hashtable_get(HashTable* hashtable, char* key, void** buffer);

// gets the amount of elements in a hashtable
size_t hashtable_count(HashTable* hashtable);

// gets the next entry in the hashtable
// returns: True if an item has been written to buffer. False if the latest item was the last one
bool hashtable_get_next(HashTable* hashtable, char** key, void** buffer);

// creates a new hashtable
HashTable* hashtable_new(size_t size);

// frees the hashtable
void hashtable_free(HashTable* hashtable);

#endif  // _HASHTABLE_H
