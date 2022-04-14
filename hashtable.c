// #include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "hashtable.h"

// http://www.cse.yorku.ca/~oz/hash.html
static unsigned long hash_str(char* input) {
	unsigned long hash = 5381;
	int c;

	while((c = *input++))
		hash = ((hash << 5) + hash) + c; // hash * 33 + c
	return hash;
}

bool hashtable_set(HashTable* hashtable, char* key, int value) {
	unsigned long hash = hash_str(key);
	unsigned int idx = hash % hashtable->size;

	if(hashtable->entries[idx].full_hash == hash) {
		hashtable->entries[idx].value = value;
		return true;
	}

	unsigned int checked = 0;
	while(hashtable->entries[idx].taken == true) {
		++idx;
		++checked;
		if(checked >= hashtable->size) {
			return false;
		}
	}

	hashtable->entries[idx].full_hash = hash;
	hashtable->entries[idx].taken = true;
	hashtable->entries[idx].value = value;
	return true;
}

bool hashtable_get(HashTable* hashtable, int* buffer, char* key) {
	unsigned long hash = hash_str(key);
	unsigned int idx = hash % hashtable->size;

	if(hashtable->entries[idx].taken == false) {
		return false;
	}

	unsigned int checked = 0;
	while(hashtable->entries[idx].full_hash != hash) {
		++idx;
		++checked;

		if(checked >= hashtable->size) {
			return false;
		}

		if(hashtable->entries[idx].taken == false) {
			return false;
		}
	}

	*buffer = hashtable->entries[idx].value;
	return true;
}

bool hashtable_clear(HashTable* hashtable, char* key) {
	unsigned long hash = hash_str(key);
	unsigned int idx = hash % hashtable->size;

	if(hashtable->entries[idx].taken == false) {
		return false;
	}

	unsigned int checked = 0;
	while(hashtable->entries[idx].full_hash != hash) {
		++idx;
		++checked;

		if(checked >= hashtable->size) {
			return false;
		}

		if(hashtable->entries[idx].taken == false) {
			return false;
		}
	}

	hashtable->entries[idx].taken = false;
	return true;
}

HashTable* hashtable_new(size_t size) {
	HashTable* hashtable = malloc(sizeof(HashTable));
	hashtable->size = size;
	hashtable->entries = calloc(size, sizeof(HashEntry)); // initialise to 0, 'taken' is implicitly false
	return hashtable;
}

void hashtable_free(HashTable* hashtable) {
	free(hashtable->entries);
	free(hashtable);
}
