#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} Counter;

int compare(const void *a, const void *b) {
    Counter *counterA = (Counter *)a;
    Counter *counterB = (Counter *)b;
    return counterB->value - counterA->value;
}

void sortCounter(Counter *counter, int size) {
    qsort(counter, size, sizeof(Counter), compare);
}

int main() {
    Counter counter[] = {{1, 20}, {2, 10}, {3, 30}, {4, 40}, {5, 50}};
    int size = sizeof(counter) / sizeof(counter[0]);

    sortCounter(counter, size);

    for(int i = 0; i < size; i++) {
        printf("Key: %d, Value: %d\n", counter[i].key, counter[i].value);
    }

    return 0;
}