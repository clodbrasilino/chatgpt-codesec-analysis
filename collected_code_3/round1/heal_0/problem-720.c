#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    char key[MAX_SIZE];
    char value[MAX_SIZE];
} Dictionary;

typedef struct {
    Dictionary dictionaries[MAX_SIZE];
    int size;
} Tuple;

void addDictionaryToTuple(Tuple *tuple, Dictionary dictionary) {
    tuple->dictionaries[tuple->size] = dictionary;
    tuple->size++;
}

int main() {
    Tuple tuple;
    tuple.size = 0;

    Dictionary dictionary;
    strcpy(dictionary.key, "key1");
    strcpy(dictionary.value, "value1");

    addDictionaryToTuple(&tuple, dictionary);

    printf("Key: %s, Value: %s\n", tuple.dictionaries[0].key, tuple.dictionaries[0].value);

    return 0;
}