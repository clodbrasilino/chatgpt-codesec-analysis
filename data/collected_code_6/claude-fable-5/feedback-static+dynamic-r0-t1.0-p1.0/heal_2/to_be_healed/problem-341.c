#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int compare_ints(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y) {
        return -1;
    }
    if (x > y) {
        return 1;
    }
    return 0;
}

int *set_to_ordered_tuple(const int *set, size_t size)
{
    int *tuple = NULL;
    size_t total_bytes = 0U;

    if (set == NULL || size == 0U) {
        return NULL;
    }

    if (size > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    total_bytes = size * sizeof(int);

    tuple = malloc(total_bytes);
    if (tuple == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(tuple, set, total_bytes);
    qsort(tuple, size, sizeof(int), compare_ints);

    return tuple;
}

int main(void)
{
    int set[] = {7, 2, 9, 4, 1};
    size_t size = sizeof(set) / sizeof(set[0]);
    size_t i = 0U;
    int *tuple = NULL;

    tuple = set_to_ordered_tuple(set, size);
    if (tuple == NULL) {
        fprintf(stderr, "Failed to create ordered tuple\n");
        return EXIT_FAILURE;
    }

    printf("(");
    for (i = 0U; i < size; i++) {
        if (i > 0U) {
            printf(", ");
        }
        printf("%d", tuple[i]);
    }
    printf(")\n");

    free(tuple);
    tuple = NULL;

    return EXIT_SUCCESS;
}