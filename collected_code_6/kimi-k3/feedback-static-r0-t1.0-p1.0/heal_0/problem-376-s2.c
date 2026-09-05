#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int first;
    int second;
} Tuple;

static int tuple_equals(const Tuple *a, const Tuple *b) {
    return a->first == b->first && a->second == b->second;
}

size_t remove_duplicate_tuples(Tuple *tuples, size_t count, const Tuple *replacement) {
    size_t i;
    size_t j;
    size_t write_index;
    size_t duplicate_count;
    int *seen;
    int is_duplicate;

    if (tuples == NULL || replacement == NULL) {
        return 0;
    }

    if (count == 0) {
        return 0;
    }

    seen = calloc(count, sizeof(int));
    if (seen == NULL) {
        return 0;
    }

    write_index = 0;

    for (i = 0; i < count; i++) {
        is_duplicate = 0;

        for (j = 0; j < i; j++) {
            if (seen[j] && tuple_equals(&tuples[i], &tuples[j])) {
                is_duplicate = 1;
                break;
            }
        }

        if (is_duplicate) {
            tuples[i] = *replacement;
            duplicate_count = 0;

            for (j = 0; j < i; j++) {
                if (seen[j] && tuple_equals(&tuples[i], &tuples[j])) {
                    duplicate_count++;
                }
            }

            if (duplicate_count > 0) {
                seen[i] = 1;
            }
        } else {
            seen[i] = 1;
        }

        write_index++;
    }

    free(seen);
    return write_index;
}

int main(void) {
    Tuple tuples[] = {
        {1, 2},
        {3, 4},
        {1, 2},
        {5, 6},
        {3, 4},
        {1, 2}
    };
    Tuple replacement = {0, 0};
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    size_t result_count;
    size_t i;

    result_count = remove_duplicate_tuples(tuples, count, &replacement);

    if (result_count == 0) {
        fprintf(stderr, "Error processing tuples\n");
        return EXIT_FAILURE;
    }

    printf("Processed tuples:\n");
    for (i = 0; i < result_count; i++) {
        printf("(%d, %d)\n", tuples[i].first, tuples[i].second);
    }

    return EXIT_SUCCESS;
}