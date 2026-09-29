#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

int find_min_difference(const Tuple *tuples, size_t count) {
    if (tuples == NULL || count == 0) {
        return -1;
    }

    int min_diff = (int)llabs((long long)tuples[0].a - (long long)tuples[0].b);

    for (size_t i = 1; i < count; i++) {
        int diff = (int)llabs((long long)tuples[i].a - (long long)tuples[i].b);
        if (diff < min_diff) {
            min_diff = diff;
        }
    }

    return min_diff;
}

int main(void) {
    Tuple tuples[] = {{10, 3}, {5, 8}, {2, 12}};
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    int min_diff = find_min_difference(tuples, count);

    if (min_diff != -1) {
        printf("%d\n", min_diff);
    }

    return 0;
}