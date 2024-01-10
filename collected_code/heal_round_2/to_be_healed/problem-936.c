#include <stdio.h>

void rearrangeTuples(const int tuples[], const int orderedList[], int size) {
    int temp[size];
    for (int i = 0; i < size; i++) {
        temp[orderedList[i]] = tuples[i];
    }
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  assignment of read-only location '*(tuples + (sizetype)((long unsigned int)i * 4))'
         */
        tuples[i] = temp[i];
    }
}

int main() {
    int tuples[] = {1, 2, 3, 4};
    int orderedList[] = {2, 3, 1, 0};
    int size = sizeof(tuples) / sizeof(tuples[0]);

    rearrangeTuples(tuples, orderedList, size);

    for (int i = 0; i < size; i++) {
        printf("%d ", tuples[i]);
    }

    return 0;
}