#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

static bool print_duplicates(const int *list, size_t count)
{
    int *sorted = NULL;
    size_t i;

    if (list == NULL || count == 0U) {
        return false;
    }

    sorted = malloc(count * sizeof(*sorted));
    if (sorted == NULL) {
        return false;
    }

    for (i = 0U; i < count; i++) {
        sorted[i] = list[i];
    }

    qsort(sorted, count, sizeof(*sorted), compare_ints);

    for (i = 1U; i < count; i++) {
        if (sorted[i] == sorted[i - 1U]) {
            if (printf("%d\n", sorted[i]) < 0) {
                free(sorted);
                return false;
            }
            while (i + 1U < count && sorted[i + 1U] == sorted[i]) {
                i++;
            }
        }
    }

    free(sorted);
    return true;
}

int main(void)
{
    int numbers[] = { 4, 2, 7, 2, 9, 4, 1, 7, 7, 3 };
    size_t count = sizeof(numbers) / sizeof(numbers[0]);

    if (!print_duplicates(numbers, count)) {
        if (fprintf(stderr, "Failed to print duplicates\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}