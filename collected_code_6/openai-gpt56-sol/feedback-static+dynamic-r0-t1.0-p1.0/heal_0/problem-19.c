#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static bool contains_duplicate(const int *array, size_t length, bool *result)
{
    int *copy;
    size_t i;

    if (result == NULL || (array == NULL && length != 0U)) {
        return false;
    }

    *result = false;

    if (length < 2U) {
        return true;
    }

    if (length > SIZE_MAX / sizeof(*copy)) {
        return false;
    }

    copy = malloc(length * sizeof(*copy));
    if (copy == NULL) {
        return false;
    }

    for (i = 0U; i < length; ++i) {
        copy[i] = array[i];
    }

    qsort(copy, length, sizeof(*copy), compare_ints);

    for (i = 1U; i < length; ++i) {
        if (copy[i] == copy[i - 1U]) {
            *result = true;
            break;
        }
    }

    free(copy);
    return true;
}

int main(void)
{
    const int numbers[] = {4, 2, 7, 1, 2};
    bool has_duplicate = false;

    if (!contains_duplicate(
            numbers,
            sizeof(numbers) / sizeof(numbers[0]),
            &has_duplicate)) {
        fputs("Unable to check the array.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(has_duplicate ? "Duplicate found." : "No duplicates found.");
    return EXIT_SUCCESS;
}