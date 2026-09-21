#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_desc(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;
    if (x < y) {
        return 1;
    }
    if (x > y) {
        return -1;
    }
    return 0;
}

int largest_number(const int *digits, size_t count, char *result, size_t result_size)
{
    int *copy;
    size_t i;

    if (digits == NULL || result == NULL || count == 0) {
        return -1;
    }
    if (result_size < count + 1) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        if (digits[i] < 0 || digits[i] > 9) {
            return -1;
        }
    }

    copy = malloc(count * sizeof(int));
    if (copy == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, digits, count * sizeof(int));
    qsort(copy, count, sizeof(int), compare_desc);

    for (i = 0; i < count; i++) {
        result[i] = (char)('0' + copy[i]);
    }
    result[count] = '\0';

    free(copy);
    return 0;
}

int main(void)
{
    int digits[] = {3, 9, 1, 5, 7, 0, 2};
    size_t count = sizeof(digits) / sizeof(digits[0]);
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[16];

    if (largest_number(digits, count, result, sizeof(result)) != 0) {
        fprintf(stderr, "Error: could not compute largest number\n");
        return EXIT_FAILURE;
    }

    if (printf("Largest number: %s\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}