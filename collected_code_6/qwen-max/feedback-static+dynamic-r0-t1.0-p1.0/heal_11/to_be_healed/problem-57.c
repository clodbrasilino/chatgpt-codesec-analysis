#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    const char **str1 = (const char **)a;
    const char **str2 = (const char **)b;
    return strcmp(*str1, *str2) > 0 ? -1 : 1;
}

char* largestNumber(const int *digits, int size) {
    char **str_digits = (char **)malloc(size * sizeof(char *));
    if (str_digits == NULL) return NULL;
    for (int i = 0; i < size; ++i) {
        str_digits[i] = (char *)malloc(12 * sizeof(char));
        if (str_digits[i] == NULL) {
            for (int j = 0; j < i; ++j) free(str_digits[j]);
            free(str_digits);
            return NULL;
        }
        snprintf(str_digits[i], 12, "%d", digits[i]);
    }

    qsort(str_digits, size, sizeof(char *), compare);

    char *result = (char *)malloc((size * 12 + 1) * sizeof(char));
    if (result == NULL) {
        for (int i = 0; i < size; ++i) free(str_digits[i]);
        free(str_digits);
        return NULL;
    }
    result[0] = '\0';
    for (int i = 0; i < size; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         */
        strncat(result, str_digits[i], 12);
        free(str_digits[i]);
    }
    free(str_digits);

    return result;
}

int main() {
    const int digits[] = {3, 30, 34, 5, 9};
    int size = 5;
    char *result = largestNumber(digits, size);
    if (result == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    printf("%s\n", result);
    free(result);
    return 0;
}