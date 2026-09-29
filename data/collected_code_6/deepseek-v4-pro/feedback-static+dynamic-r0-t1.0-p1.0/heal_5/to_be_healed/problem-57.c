#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_desc(const void *a, const void *b) {
    return (*(const char *)b - *(const char *)a);
}

void largest_number_from_digits(const char *digits, char *result, size_t result_size) {
    if (result == NULL || result_size == 0) {
        return;
    }

    if (digits == NULL) {
        result[0] = '\0';
        return;
    }

    size_t len = strnlen(digits, result_size);
    if (len == 0) {
        result[0] = '\0';
        return;
    }

    if (len >= result_size) {
        len = result_size - 1;
    }

    if (len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result, digits, len);
    }
    result[len] = '\0';
    qsort(result, len, sizeof(char), compare_desc);
}

int main(void) {
    const char digits[] = "9371458260";
    char *result = NULL;
    size_t result_size = 32;

    result = (char *)calloc(result_size, sizeof(char));
    if (result == NULL) {
        return 1;
    }

    largest_number_from_digits(digits, result, result_size);
    printf("%s\n", result);
    free(result);

    return 0;
}