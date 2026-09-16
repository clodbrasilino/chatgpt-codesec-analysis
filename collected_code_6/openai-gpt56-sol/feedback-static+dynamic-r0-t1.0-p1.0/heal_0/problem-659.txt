#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static void print_duplicates(const int *values, size_t count)
{
    int *sorted = NULL;
    size_t i = 0;

    if (values == NULL || count < 2U) {
        return;
    }

    if (count > SIZE_MAX / sizeof(*sorted)) {
        fputs("Input is too large.\n", stderr);
        return;
    }

    sorted = malloc(count * sizeof(*sorted));
    if (sorted == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return;
    }

    for (i = 0; i < count; ++i) {
        sorted[i] = values[i];
    }

    qsort(sorted, count, sizeof(*sorted), compare_ints);

    i = 0;
    while (i < count) {
        size_t next = i + 1U;

        while (next < count && sorted[next] == sorted[i]) {
            ++next;
        }

        if (next - i > 1U) {
            printf("%d\n", sorted[i]);
        }

        i = next;
    }

    free(sorted);
}

int main(void)
{
    int values[] = {4, 2, 7, 4, 2, 9, 2, 8, 7};
    const size_t count = sizeof(values) / sizeof(values[0]);

    print_duplicates(values, count);

    if (ferror(stdout)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}