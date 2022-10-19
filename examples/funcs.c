#include <stdio.h>

#include "hashtable.h"

#define HASHTABLE_SIZE 1000

typedef void (*greeter_func)(char*);

void greet(char* name) {
    printf("Hello there %s\n", name);
}

void goodbye(char* name) {
    printf("I'll see you later, %s\n", name);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Please supply a name\n");
        return 1;
    }

    HashTable* my_hashtable = hashtable_new(HASHTABLE_SIZE);

    hashtable_set(my_hashtable, "greeter_func", greet);
    hashtable_set(my_hashtable, "goodbye_func", goodbye);

    size_t amt = hashtable_count(my_hashtable);
    printf("The hashtable has %lu entries\n", amt);

    greeter_func greet, goodbye;
    hashtable_get(my_hashtable, "greeter_func", (void**)&greet);
    hashtable_get(my_hashtable, "goodbye_func", (void**)&goodbye);

    greet(argv[1]);
    goodbye(argv[1]);

    hashtable_free(my_hashtable);

    return 0;
}
