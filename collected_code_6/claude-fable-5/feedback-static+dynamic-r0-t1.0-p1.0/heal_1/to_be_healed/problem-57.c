#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int compare_desc(const void *a, const void *b)
{
    int da = *(const int *)a;
    int db = *(const int *)b;

    if (da < db) {
        return 1;
    }
    if (da > db) {
        return -1;
    }
    return 0;
}

static int largest_number(const int *digits, size_t count, char *result, size_t result_size)
{
    int *sorted = NULL;
    size_t i;

    if ((digits == NULL) || (result == NULL) || (count == 0U)) {
        return -1;
    }

    if (result_size < (count + 1U)) {
        return -1;
    }

    for (i = 0U; i < count; i++) {
        if ((digits[i] < 0) || (digits[i] > 9)) {
            return -1;
        }
    }

    sorted = (int *)malloc(count * sizeof(int));
    if (sorted == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    (void)memcpy(sorted, digits, count * sizeof(int));
    qsort(sorted, count, sizeof(int), compare_desc);

    for (i = 0U; i < count; i++) {
        result[i] = (char)('0' + sorted[i]);
    }
    result[count] = '\0';

    free(sorted);
    return 0;
}

int main(void)
{
    size_t count = 0U;
    size_t i;
    int *digits = NULL;
    char *result = NULL;
    unsigned long input_count = 0UL;

    printf("Enter the number of digits: ");
    if (scanf("%lu", &input_count) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if ((input_count == 0UL) || (input_count > 1000UL)) {
        fprintf(stderr, "Count must be between 1 and 1000\n");
        return EXIT_FAILURE;
    }

    count = (size_t)input_count;

    digits = (int *)malloc(count * sizeof(int));
    if (digits == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    result = (char *)malloc(count + 1U);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(digits);
        return EXIT_FAILURE;
    }

    printf("Enter %lu digits (0-9):\n", input_count);
    for (i = 0U; i < count; i++) {
        if (scanf("%d", &digits[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(digits);
            free(result);
            return EXIT_FAILURE;
        }
        if ((digits[i] < 0) || (digits[i] > 9)) {
            fprintf(stderr, "Digit must be between 0 and 9\n");
            free(digits);
            free(result);
            return EXIT_FAILURE;
        }
    }

    if (largest_number(digits, count, result, count + 1U) != 0) {
        fprintf(stderr, "Failed to compute largest number\n");
        free(digits);
        free(result);
        return EXIT_FAILURE;
    }

    printf("Largest number: %s\n", result);

    free(digits);
    free(result);
    return EXIT_SUCCESS;
}