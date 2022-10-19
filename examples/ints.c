#include <stdint.h>
#include <stdio.h>

#include "hashtable.h"

#define HASHTABLE_SIZE 1000

int main() {
    HashTable* my_hashtable = hashtable_new(HASHTABLE_SIZE);

    int64_t my_values[] = {2000, 1000};
    hashtable_set(my_hashtable, "Apples", my_values + 0);
    hashtable_set(my_hashtable, "Oranges", my_values + 1);

    int64_t *apples, *oranges;
    hashtable_get(my_hashtable, "Apples", (void**)&apples);
    hashtable_get(my_hashtable, "Oranges", (void**)&oranges);

    printf("Apples: %ld\nOranges: %ld\n", *apples, *oranges);

    hashtable_free(my_hashtable);

    return 0;
}
