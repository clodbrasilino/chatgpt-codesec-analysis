#include <stdio.h>

void clearTuples(int *tuples, int size) {
    for(int i = 0; i < size; i++) {
        tuples[i] = 0;
    }
}

int main() {
    int tuples[5] = {1, 2, 3, 4, 5};

    clearTuples(tuples, 5);

    for(int i = 0; i < 5; i++) {
        printf("%d ", tuples[i]);
    }

    return 0;
}