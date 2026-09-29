#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TUPLES 100
#define MAX_STRING_LENGTH 50

typedef struct {
    char first_item[MAX_STRING_LENGTH];
    int second_item;
} Tuple;

int compare_tuples(const void *a, const void *b) {
    return strcmp(((Tuple *)a)->first_item, ((Tuple *)b)->first_item);
}

void sort_tuples(Tuple *tuples, int count) {
    qsort(tuples, count, sizeof(Tuple), compare_tuples);
}

int main() {
    Tuple tuples[] = {
        {"banana", 2},
        {"apple", 1},
        {"orange", 3}
    };
    int count = sizeof(tuples) / sizeof(tuples[0]);

    sort_tuples(tuples, count);

    for (int i = 0; i < count; ++i) {
        printf("%s %d\n", tuples[i].first_item, tuples[i].second_item);
    }

    return 0;
}