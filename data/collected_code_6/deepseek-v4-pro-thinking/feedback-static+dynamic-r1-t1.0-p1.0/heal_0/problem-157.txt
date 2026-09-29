#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t count;
    int value;
} Run;

int rle_decode(const Run *runs, size_t run_count, int **decoded, size_t *decoded_count) {
    if (decoded == NULL || decoded_count == NULL) {
        return -1;
    }
    if (runs == NULL && run_count > 0) {
        return -1;
    }

    size_t total = 0;
    for (size_t i = 0; i < run_count; ++i) {
        if (runs[i].count > (size_t)-1 - total) {
            return -1;
        }
        total += runs[i].count;
    }

    if (total == 0) {
        *decoded = NULL;
        *decoded_count = 0;
        return 0;
    }

    int *output = NULL;
    if (total > (size_t)-1 / sizeof(*output)) {
        return -1;
    }
    output = malloc(total * sizeof(*output));
    if (output == NULL) {
        return -1;
    }

    size_t pos = 0;
    for (size_t i = 0; i < run_count; ++i) {
        for (size_t j = 0; j < runs[i].count; ++j) {
            output[pos++] = runs[i].value;
        }
    }

    *decoded = output;
    *decoded_count = total;
    return 0;
}

int main(void) {
    Run runs[] = {
        {3, 1},
        {2, 4},
        {5, 2}
    };

    int *decoded = NULL;
    size_t decoded_count = 0;

    if (rle_decode(runs, sizeof(runs) / sizeof(runs[0]), &decoded, &decoded_count) != 0) {
        fprintf(stderr, "Run-length decoding failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < decoded_count; ++i) {
        printf("%d ", decoded[i]);
    }
    printf("\n");

    free(decoded);
    return EXIT_SUCCESS;
}