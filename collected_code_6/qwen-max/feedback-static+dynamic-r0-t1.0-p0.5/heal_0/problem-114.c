#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *item;
    int frequency;
} Tuple;

int compare(const void *a, const void *b) {
    return strcmp(((Tuple *)a)->item, ((Tuple *)b)->item);
}

void assignFrequency(Tuple *tuples, int count) {
    if (count <= 0) return;
    qsort(tuples, count, sizeof(Tuple), compare);

    int current_frequency = 1;
    for (int i = 1; i < count; ++i) {
        if (strcmp(tuples[i].item, tuples[i - 1].item) == 0) {
            ++current_frequency;
        } else {
            tuples[i - 1].frequency = current_frequency;
            current_frequency = 1;
        }
    }
    tuples[count - 1].frequency = current_frequency;
}

int main() {
    Tuple tuples[] = {{"apple", 0}, {"banana", 0}, {"apple", 0}, {"orange", 0}, {"banana", 0}, {"apple", 0}};
    int count = sizeof(tuples) / sizeof(tuples[0]);

    assignFrequency(tuples, count);

    for (int i = 0; i < count; ++i) {
        printf("%s: %d\n", tuples[i].item, tuples[i].frequency);
    }

    return 0;
}