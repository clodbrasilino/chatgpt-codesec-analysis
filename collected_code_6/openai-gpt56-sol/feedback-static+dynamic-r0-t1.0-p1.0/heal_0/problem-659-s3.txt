#include <stdio.h>
#include <stdlib.h>

static int compare_integers(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static void print_duplicates(const int *values, size_t count)
{
    int *sorted;
    size_t i;

    if (values == NULL || count < 2) {
        return;
    }

    if (count > SIZE_MAX / sizeof(*sorted)) {
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

    qsort(sorted, count, sizeof(*sorted), compare_integers);

    i = 0;
    while (i < count) {
        size_t next = i + 1;

        while (next < count && sorted[next] == sorted[i]) {
            ++next;
        }

        if (next - i > 1) {
            printf("%d\n", sorted[i]);
        }

        i = next;
    }

    free(sorted);
}

int main(void)
{
    int values[] = {4, 2, 7, 4, 9, 2, 2, 5, 7};
    const size_t count = sizeof(values) / sizeof(values[0]);

    print_duplicates(values, count);

    if (ferror(stdout)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}