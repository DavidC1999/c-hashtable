#include "hashtable.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// http://www.cse.yorku.ca/~oz/hash.html
static unsigned long hash_str(char* input) {
    unsigned long hash = 5381;
    int c;

    while ((c = *input++))
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    return hash;
}

bool hashtable_set(HashTable* hashtable, char* key, void* value) {
    unsigned long hash = hash_str(key);
    unsigned int idx = hash % hashtable->size;

    char* existing_key = hashtable->entries[idx].key;

    if (existing_key != NULL && strcmp(existing_key, key) == 0) {
        hashtable->entries[idx].value = value;
        return true;
    }

    unsigned int checked = 0;
    while (hashtable->entries[idx].value != NULL) {
        ++idx;
        ++checked;
        if (checked >= hashtable->size) {
            return false;
        }
    }

    size_t key_size = sizeof(char) * (strlen(key) + 1);
    hashtable->entries[idx].key = malloc(key_size);
    strncpy(hashtable->entries[idx].key, key, key_size);
    hashtable->entries[idx].value = value;
    return true;
}

bool hashtable_get(HashTable* hashtable, char* key, void** buffer) {
    unsigned long hash = hash_str(key);
    unsigned int idx = hash % hashtable->size;

    if (hashtable->entries[idx].value == NULL) {
        return false;
    }

    unsigned int checked = 0;
    while (hashtable->entries[idx].key != NULL && strcmp(hashtable->entries[idx].key, key) != 0) {
        ++idx;
        ++checked;

        if (checked >= hashtable->size) {
            return false;
        }

        if (hashtable->entries[idx].value == NULL) {
            return false;
        }
    }

    *buffer = hashtable->entries[idx].value;
    return true;
}

size_t hashtable_count(HashTable* hashtable) {
    size_t count = 0;

    for (unsigned int i = 0; i < hashtable->size; ++i) {
        if (hashtable->entries[i].value != NULL) ++count;
    }

    return count;
}

bool hashtable_get_next(HashTable* hashtable, char** key, void** buffer) {
    static unsigned int idx = -1;

    ++idx;

    while (hashtable->entries[idx].value == NULL) {
        ++idx;
        if (idx >= hashtable->size) {
            idx = 0;
            return false;
        }
    }

    *key = hashtable->entries[idx].key;
    *buffer = hashtable->entries[idx].value;

    return true;
}

HashTable* hashtable_new(size_t size) {
    HashTable* hashtable = malloc(sizeof(HashTable));
    hashtable->size = size;
    hashtable->entries = calloc(size, sizeof(HashEntry));
    return hashtable;
}

void hashtable_free(HashTable* hashtable) {
    for (size_t i = 1; i < hashtable->size; ++i) {
        free(hashtable->entries[i].key);
    }
    free(hashtable->entries);
    free(hashtable);
}
