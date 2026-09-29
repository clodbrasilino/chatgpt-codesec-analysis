#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int *set_to_ordered_tuple(const int *set, size_t count)
{
    int *tuple;

    if (set == NULL || count == 0) {
        return NULL;
    }

    tuple = malloc(count * sizeof(*tuple));
    if (tuple == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(tuple, set, count * sizeof(*tuple));
    qsort(tuple, count, sizeof(*tuple), compare_ints);

    return tuple;
}

void print_tuple(const int *tuple, size_t count)
{
    size_t i;

    if (tuple == NULL || count == 0) {
        printf("()\n");
        return;
    }

    printf("(");
    for (i = 0; i < count; i++) {
        printf("%d", tuple[i]);
        if (i + 1 < count) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void)
{
    int set[] = { 42, 7, 19, 3, 88, 1 };
    size_t count = sizeof(set) / sizeof(set[0]);
    int *tuple;

    tuple = set_to_ordered_tuple(set, count);
    if (tuple == NULL) {
        fprintf(stderr, "Failed to create ordered tuple\n");
        return EXIT_FAILURE;
    }

    printf("Set: ");
    print_tuple(set, count);

    printf("Ordered tuple: ");
    print_tuple(tuple, count);

    free(tuple);
    tuple = NULL;

    return EXIT_SUCCESS;
}