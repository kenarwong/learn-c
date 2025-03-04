#include <stdio.h>
#include <math.h>
#include "hash_table.h"

int main() {

    ht_hash_table* ht = ht_new();

    ht_insert(ht, "key1", "apple");
    ht_insert(ht, "key2", "banana");
    ht_insert(ht, "key3", "cherry");

    assert(strcmp(ht_search(ht, "key1"), "apple") == 0);
    assert(strcmp(ht_search(ht, "key2"), "banana") == 0);
    assert(strcmp(ht_search(ht, "key3"), "cherry") == 0);

    ht_insert(ht, "key1", "avocado");
    assert(strcmp(ht_search(ht, "key1"), "apple") != 0);

    ht_delete(ht, "key2");
    assert(ht_search(ht, "key2") == NULL);

    ht_insert(ht, "key2", "beef");
    assert(strcmp(ht_search(ht, "key2"), "beef") == 0);

    printf("--- Testing resizing ---\n");

    printf("ht->size: %d\n", ht->size);
    printf("ht->count: %d\n", ht->count);

    printf("--- Resize up ---\n");

    printf("Adding items up to 70%%\n");
    int n = ceil(ht->size * .7);
    printf("n: %d\n", n);

    char key[10];
    char value[10];

    for(int i = 4; i <= n; i++) {
        sprintf(key, "key%d", i);
        sprintf(value, "value%d", i);
        ht_insert(ht, key, value);
    }

    printf("Not yet resized up\n");
    printf("ht->size: %d\n", ht->size);
    printf("ht->count: %d\n", ht->count);

    printf("Adding one more item\n");
    sprintf(key, "key%d", n+1);
    sprintf(value,"value%d", n+1);
    printf("key: %s\n", key);
    ht_insert(ht, key, value);

    printf("Resized up\n");
    printf("ht->size: %d\n", ht->size);
    printf("ht->count: %d\n", ht->count);

    printf("--- Resize down ---\n");
    printf("Removing items down to 10%%\n");
    int n2 = floor(ht->size * .1);
    printf("n2: %d\n", n2);

    for(int i = n+1; i > n2; i--) {
        sprintf(key, "key%d", i);
        ht_delete(ht, key);
    }

    printf("Not yet resized down\n");
    printf("ht->size: %d\n", ht->size);
    printf("ht->count: %d\n", ht->count);

    printf("Removing one more item\n");
    sprintf(key, "key%d", n2);
    printf("key: %s\n", key);
    ht_delete(ht, key);

    printf("Resized down\n");
    printf("ht->size: %d\n", ht->size);
    printf("ht->count: %d\n", ht->count);

    ht_del_hash_table(ht);
}