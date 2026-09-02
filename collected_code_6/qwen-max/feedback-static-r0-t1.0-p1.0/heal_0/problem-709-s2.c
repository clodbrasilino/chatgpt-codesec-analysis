#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int key;
    char value[256];
} Tuple;

int compare(const void *a, const void *b) {
    return strcmp(((Tuple *)a)->value, ((Tuple *)b)->value);
}

int count_unique_keys_for_each_value(Tuple *tuples, int size) {
    qsort(tuples, size, sizeof(Tuple), compare);

    int count = 1;
    for (int i = 1; i < size; ++i) {
        if (strcmp(tuples[i].value, tuples[i-1].value)) {
            count++;
        }
    }
    return count;
}

int main() {
    Tuple tuples[] = {
        {1, "apple"},
        {2, "orange"},
        {3, "apple"},
        {4, "banana"},
        {5, "orange"},
        {6, "banana"}
    };

    int size = sizeof(tuples) / sizeof(tuples[0]);
    int unique_count = count_unique_keys_for_each_value(tuples, size);

    printf("Unique keys for each value: %d\n", unique_count);

    return 0;
}