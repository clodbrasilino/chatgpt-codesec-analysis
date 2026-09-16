#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int first;
    int second;
} Tuple;

int extract_nth_element(const Tuple *tuples, size_t count, size_t n, Tuple *result) {
    if (tuples == NULL || result == NULL || n >= count) {
        return -1;
    }
    *result = tuples[n];
    return 0;
}

int main(void) {
    Tuple tuples[] = {
        {1, 2},
        {3, 4},
        {5, 6}
    };
    Tuple output;

    if (extract_nth_element(tuples, sizeof(tuples) / sizeof(tuples[0]), 1, &output) != 0) {
        fprintf(stderr, "Failed to extract element\n");
        return EXIT_FAILURE;
    }

    printf("%d %d\n", output.first, output.second);
    return EXIT_SUCCESS;
}