#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} Counter;

int compare(const void *a, const void *b) {
    Counter *counterA = (Counter *)a;
    Counter *counterB = (Counter *)b;
    return (counterB->value - counterA->value);
}

void sortCounter(Counter *counter, int n) {
    qsort(counter, n, sizeof(Counter), compare);
}

int main() {
    Counter counter[] = {{1, 10}, {2, 5}, {3, 20}, {4, 15}};
    int n = sizeof(counter) / sizeof(counter[0]);

    sortCounter(counter, n);

    for(int i = 0; i < n; i++) {
        printf("Key: %d, Value: %d\n", counter[i].key, counter[i].value);
    }

    return 0;
}