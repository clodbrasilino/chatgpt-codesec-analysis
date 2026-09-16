#include <stdio.h>
#include <stdlib.h>

static int generate_tuples_recursive(
    const int *set,
    size_t set_size,
    size_t tuple_length,
    size_t depth,
    int *tuple
) {
    size_t i;

    if (depth == tuple_length) {
        printf("(");
        for (i = 0; i < tuple_length; ++i) {
            if (i > 0) {
                printf(", ");
            }
            printf("%d", tuple[i]);
        }
        printf(")\n");
        return ferror(stdout) ? -1 : 0;
    }

    for (i = 0; i < set_size; ++i) {
        tuple[depth] = set[i];
        if (generate_tuples_recursive(
                set,
                set_size,
                tuple_length,
                depth + 1,
                tuple
            ) != 0) {
            return -1;
        }
    }

    return 0;
}

static int generate_ordered_tuples(
    const int *set,
    size_t set_size,
    size_t tuple_length
) {
    int *tuple;
    int result;

    if (set == NULL && set_size != 0) {
        return -1;
    }

    if (tuple_length == 0) {
        return printf("()\n") < 0 ? -1 : 0;
    }

    if (set_size == 0 || tuple_length > SIZE_MAX / sizeof(*tuple)) {
        return set_size == 0 ? 0 : -1;
    }

    tuple = malloc(tuple_length * sizeof(*tuple));
    if (tuple == NULL) {
        return -1;
    }

    result = generate_tuples_recursive(
        set,
        set_size,
        tuple_length,
        0,
        tuple
    );

    free(tuple);
    return result;
}

int main(void) {
    const int set[] = {1, 2, 3};
    const size_t set_size = sizeof(set) / sizeof(set[0]);
    const size_t tuple_length = 2;

    if (generate_ordered_tuples(set, set_size, tuple_length) != 0) {
        fprintf(stderr, "Failed to generate ordered tuples.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}