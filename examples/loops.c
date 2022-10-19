#include <stdint.h>
#include <stdio.h>

#include "hashtable.h"

int main() {
    HashTable* my_hashtable = hashtable_new(20);

    uint64_t ints[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    hashtable_set(my_hashtable, "a", ints + 0);
    hashtable_set(my_hashtable, "b", ints + 1);
    hashtable_set(my_hashtable, "c", ints + 2);
    hashtable_set(my_hashtable, "d", ints + 3);
    hashtable_set(my_hashtable, "e", ints + 4);
    hashtable_set(my_hashtable, "f", ints + 5);
    hashtable_set(my_hashtable, "g", ints + 6);
    hashtable_set(my_hashtable, "h", ints + 7);
    hashtable_set(my_hashtable, "h", ints + 8);
    hashtable_set(my_hashtable, "h", ints + 9);

    char* key;
    int64_t* value_ptr;
    while (hashtable_get_next(my_hashtable, &key, (void**)&value_ptr)) {
        printf("%s: %ld\n", key, *value_ptr);
    }

    return 0;
}
