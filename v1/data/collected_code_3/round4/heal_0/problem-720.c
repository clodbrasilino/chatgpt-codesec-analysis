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

void addDictionaryToTuple(Tuple *tuple, Dictionary dict) {
    tuple->dict[tuple->size] = dict;
    tuple->size++;
}

int main() {
    Tuple tuple;
    tuple.size = 0;

    Dictionary dict1;
    strcpy(dict1.key, "key1");
    dict1.value = 1;

    Dictionary dict2;
    strcpy(dict2.key, "key2");
    dict2.value = 2;

    addDictionaryToTuple(&tuple, dict1);
    addDictionaryToTuple(&tuple, dict2);

    for(int i = 0; i < tuple.size; i++) {
        printf("Key: %s, Value: %d\n", tuple.dict[i].key, tuple.dict[i].value);
    }

    return 0;
}