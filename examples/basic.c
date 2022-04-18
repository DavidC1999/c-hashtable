#include <stdio.h>
#include "hashtable.h"

#define HASHTABLE_SIZE 1000

int main() {
	HashTable* my_hashtable = hashtable_new(HASHTABLE_SIZE);

	hashtable_set(my_hashtable, "Apples", 2000);
	hashtable_set(my_hashtable, "Oranges", 1000);

	int apples, oranges;
	hashtable_get(my_hashtable, &apples, "Apples");
	hashtable_get(my_hashtable, &oranges, "Oranges");

	printf("Apples: %d\nOranges: %d\n", apples, oranges);

	hashtable_free(my_hashtable);

	return 0;
}
