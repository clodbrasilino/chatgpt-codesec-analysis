#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int key;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char value[10];
} Tuple;

int compare(const void *a, const void *b) {
    return ((Tuple *)a)->key - ((Tuple *)b)->key;
}

void find_min_k(Tuple *tuples, int n, int k) {
    qsort(tuples, n, sizeof(Tuple), compare);
    for (int i = 0; i < k && i < n; ++i) {
        printf("(%d, %s)\n", tuples[i].key, tuples[i].value);
    }
}

int main() {
    Tuple tuples[] = {{5, "E"}, {9, "I"}, {1, "A"}, {8, "H"}, {2, "B"}, {7, "G"}, {3, "C"}, {6, "F"}, {4, "D"}};
    int n = sizeof(tuples) / sizeof(tuples[0]);
    int k = 3;
    find_min_k(tuples, n, k);
    return 0;
}