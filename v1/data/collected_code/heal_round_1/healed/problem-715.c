#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_LENGTH 100

typedef struct {
    int* values;
    int size;
} Tuple;

Tuple convertStringToTuple(const char* str) {
    char* copy = malloc(MAX_LENGTH);
    if (!copy) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }

    strncpy(copy, str, MAX_LENGTH);

    int length = strlen(copy);
    int* values = calloc(length, sizeof(int));
    if (!values) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }

    int size = 0;
    char* token = strtok(copy, " ");
    while (token != NULL && size < length) {
        long val = strtol(token, NULL, 10);
        if (val > INT_MAX || val < INT_MIN) {
            fprintf(stderr, "Number out of range\n");
            exit(1);
        }
        values[size++] = (int)val;
        token = strtok(NULL, " ");
    }
    
    Tuple tuple;
    tuple.values = values;
    tuple.size = size;

    free(copy);

    return tuple;
}

int main() {
    const char* str = "5 10 15 20";
    Tuple tuple = convertStringToTuple(str);
    
    printf("Tuple: ");
    for (int i = 0; i < tuple.size; i++) {
        printf("%d ", tuple.values[i]);
    }
    printf("\n");

    free(tuple.values);

    return 0;
}