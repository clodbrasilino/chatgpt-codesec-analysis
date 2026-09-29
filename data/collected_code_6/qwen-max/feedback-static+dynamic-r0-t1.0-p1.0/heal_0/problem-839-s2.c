#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TUPLES 100
#define MAX_LENGTH 50

typedef struct {
    char first[MAX_LENGTH];
    int second;
} Tuple;

int compare(const void *a, const void *b) {
    return strcmp(((Tuple *)a)->first, ((Tuple *)b)->first);
}

void print_tuples(Tuple tuples[], int size) {
    for (int i = 0; i < size; i++) {
        printf("('%s', %d)\n", tuples[i].first, tuples[i].second);
    }
}

int main() {
    Tuple tuples[MAX_TUPLES] = {
        {"banana", 4},
        {"apple", 2},
        {"orange", 3},
        {"grape", 6}
    };
    int size = 4;

    qsort(tuples, size, sizeof(Tuple), compare);

    print_tuples(tuples, size);

    return 0;
}