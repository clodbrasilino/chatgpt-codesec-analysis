#include <stdio.h>

typedef struct {
    int first;
    int second;
} Tuple;

void addListToTuples(Tuple* tuples, int* list, int size) {
    for(int i = 0; i < size; i++) {
        tuples[i].first += list[i];
        tuples[i].second += list[i];
    }
}

int main() {
    Tuple tuples[3] = {{1, 2}, {3, 4}, {5, 6}};
    int list[3] = {1, 2, 3};
    int size = sizeof(list)/sizeof(list[0]);

    addListToTuples(tuples, list, size);

    for(int i = 0; i < size; i++) {
        printf("Tuple %d: (%d, %d)\n", i+1, tuples[i].first, tuples[i].second);
    }

    return 0;
}