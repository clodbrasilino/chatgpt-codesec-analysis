#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TUPLE_SIZE 100
#define MAX_TUPLE_COUNT 100

struct Tuple {
    char arr[MAX_TUPLE_SIZE][MAX_TUPLE_COUNT];
    int size;
};

void initTuple(struct Tuple* tuple) {
    tuple->size = 0;
}

void addElement(struct Tuple* tuple, char* el) {
    if(tuple->size < MAX_TUPLE_COUNT) {
        strcpy(tuple->arr[tuple->size++], el);
    } else {
        printf("Tuple Max Size Reached.");
        exit(1);
    }
}

struct Tuple joinTuples(struct Tuple tuple1, struct Tuple tuple2) {
    struct Tuple result;
    initTuple(&result);

    if(strcmp(tuple1.arr[0], tuple2.arr[0]) == 0) {
        for(int i = 0; i < tuple1.size; i++) {
            addElement(&result, tuple1.arr[i]);
        }
        for(int i = 1; i < tuple2.size; i++) {
            addElement(&result, tuple2.arr[i]);
        }
    } else {
        printf("No Similar Initial Elements Detected");
        exit(1);
    }

    return result;
}

int main() {
    struct Tuple tuple1, tuple2, result;

    initTuple(&tuple1);
    addElement(&tuple1, "Hello Test");
    addElement(&tuple1, "Hello Test2");

    initTuple(&tuple2);
    addElement(&tuple2, "Hello Test");
    addElement(&tuple2, "Hello Test3");

    result = joinTuples(tuple1, tuple2);

    for(int i = 0; i < result.size; i++) {
        printf("%s\n", result.arr[i]);
    }

    return 0;
}