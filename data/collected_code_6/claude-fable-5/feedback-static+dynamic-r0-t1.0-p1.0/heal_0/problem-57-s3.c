#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int compare_desc(const void *a, const void *b)
{
    int da = *(const int *)a;
    int db = *(const int *)b;
    return db - da;
}

static char *largest_number(const int *digits, size_t count)
{
    char *result = NULL;
    int *copy = NULL;
    size_t i;

    if (digits == NULL || count == 0U) {
        return NULL;
    }

    for (i = 0U; i < count; i++) {
        if (digits[i] < 0 || digits[i] > 9) {
            return NULL;
        }
    }

    copy = malloc(count * sizeof(int));
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, digits, count * sizeof(int));
    qsort(copy, count, sizeof(int), compare_desc);

    result = malloc(count + 1U);
    if (result == NULL) {
        free(copy);
        return NULL;
    }

    for (i = 0U; i < count; i++) {
        result[i] = (char)('0' + copy[i]);
    }
    result[count] = '\0';

    free(copy);
    return result;
}

int main(void)
{
    int digits[] = {3, 9, 4, 1, 7, 0, 5};
    size_t count = sizeof(digits) / sizeof(digits[0]);
    char *largest;

    largest = largest_number(digits, count);
    if (largest == NULL) {
        fprintf(stderr, "Error: failed to compute the largest number\n");
        return EXIT_FAILURE;
    }

    if (printf("Largest number: %s\n", largest) < 0) {
        free(largest);
        return EXIT_FAILURE;
    }

    free(largest);
    return EXIT_SUCCESS;
}