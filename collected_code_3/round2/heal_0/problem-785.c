#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMBERS 100

void convertTupleStringToInt(char *tupleString, int *tupleInt, int *size) {
    char *token = strtok(tupleString, ", ");
    while (token != NULL) {
        tupleInt[*size] = atoi(token);
        (*size)++;
        token = strtok(NULL, ", ");
    }
}

int main() {
    char tupleString[] = "1, 2, 3, 4, 5";
    int tupleInt[MAX_NUMBERS];
    int size = 0;

    convertTupleStringToInt(tupleString, tupleInt, &size);

    printf("Converted tuple: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", tupleInt[i]);
    }

    return 0;
}