#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 256
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

void sortTuples(char tuples[][MAX_SIZE], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (strcmp(tuples[j], tuples[j + 1]) > 0) {
                char temp[MAX_SIZE];
                memcpy(temp, tuples[j], MIN(strlen(tuples[j]), MAX_SIZE-1));
                temp[MIN(strlen(tuples[j]), MAX_SIZE-1)] = '\0';
                
                memcpy(tuples[j], tuples[j + 1], MIN(strlen(tuples[j + 1]), MAX_SIZE-1));
                tuples[j][MIN(strlen(tuples[j]), MAX_SIZE-1)] = '\0';
                
                memcpy(tuples[j + 1], temp, MIN(strlen(temp), MAX_SIZE-1));
                tuples[j + 1][MIN(strlen(temp), MAX_SIZE-1)] = '\0';
            }
        }
    }
}

int main() {
    char tuples[][MAX_SIZE] = {"b2", "a1", "c3"};
    int size = sizeof(tuples) / sizeof(tuples[0]);
    sortTuples(tuples, size);
    for (int i = 0; i < size; i++) {
        printf("(%s) ", tuples[i]);
    }
    return 0;
}