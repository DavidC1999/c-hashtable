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

bool hashtable_set(HashTable* hashtable, char* key, void* value) {
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

bool hashtable_set_int(HashTable* hashtable, char* key, int value) {
	if(hashtable->type != INT_T) return false;

	int* new_value = malloc(sizeof(int));
	*new_value = value;

	return hashtable_set(hashtable, key, new_value);
}

bool hashtable_get(HashTable* hashtable, HashEntry* buffer, char* key) {
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

	buffer->full_hash = hashtable->entries[idx].full_hash;
	buffer->taken = hashtable->entries[idx].taken;
	buffer->value = hashtable->entries[idx].value;
	return true;
}

bool hashtable_get_int(HashTable* hashtable, int* buffer, char* key) {
	HashEntry entry_buffer;
	if(!hashtable_get(hashtable, &entry_buffer, key)) return false;
	
	*buffer = *(int*)entry_buffer.value;
	return true;
}

HashTable* hashtable_new(enum HashTableType type, size_t size) {
	HashTable* hashtable = malloc(sizeof(HashTable));
	hashtable->type = type;
	hashtable->size = size;
	hashtable->entries = calloc(size, sizeof(HashEntry)); // initialise to 0, 'taken' is implicitly false
	return hashtable;
}

void hashtable_free(HashTable* hashtable) {
	if(hashtable->type == INT_T) {
		for(size_t i = 0; i < hashtable->size; ++i)
			free(hashtable->entries[i].value);
	}
	free(hashtable->entries);
	free(hashtable);
}
