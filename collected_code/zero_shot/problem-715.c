#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int* values;
    int size;
} Tuple;

Tuple convertStringToTuple(const char* str) {
    int length = strlen(str);
    int* values = malloc(length * sizeof(int));
    int size = 0;
    
    char* token = strtok((char*)str, " ");
    while (token != NULL) {
        values[size++] = atoi(token);
        token = strtok(NULL, " ");
    }
    
    Tuple tuple;
    tuple.values = values;
    tuple.size = size;
    
    return tuple;
}

int main() {
    const char* str = "5 10 15 20";
    Tuple tuple = convertStringToTuple(str);
    
    printf("Tuple: ");
    for (int i = 0; i < tuple.size; i++) {
        printf("%d ", tuple.values[i]);
    }
    
    free(tuple.values);
    
    return 0;
}