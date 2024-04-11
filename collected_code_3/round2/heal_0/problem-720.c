#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    char key[MAX_SIZE];
    int value;
} Dictionary;

typedef struct {
    Dictionary dict[MAX_SIZE];
    int size;
} Tuple;

void add_to_tuple(Tuple *tuple, char *key, int value) {
    strcpy(tuple->dict[tuple->size].key, key);
    tuple->dict[tuple->size].value = value;
    tuple->size++;
}

int main() {
    Tuple tuple;
    tuple.size = 0;

    add_to_tuple(&tuple, "key1", 1);
    add_to_tuple(&tuple, "key2", 2);
    add_to_tuple(&tuple, "key3", 3);

    for(int i = 0; i < tuple.size; i++) {
        printf("Key: %s, Value: %d\n", tuple.dict[i].key, tuple.dict[i].value);
    }

    return 0;
}