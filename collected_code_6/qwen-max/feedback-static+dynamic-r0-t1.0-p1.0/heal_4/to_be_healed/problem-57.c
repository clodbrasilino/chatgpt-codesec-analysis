#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* largestNumber(const int *digits, int size) {
    char **str_digits = (char **)malloc(size * sizeof(char *));
    if (str_digits == NULL) return NULL;
    for (int i = 0; i < size; ++i) {
        str_digits[i] = (char *)malloc(3 * sizeof(char));
        if (str_digits[i] == NULL) {
            for (int j = 0; j < i; ++j) free(str_digits[j]);
            free(str_digits);
            return NULL;
        }
        snprintf(str_digits[i], 3 * sizeof(char), "%d", digits[i]);
    }

    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - 1 - i; ++j) {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char temp1[6];
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char temp2[6];
            snprintf(temp1, 6, "%s%s", str_digits[j], str_digits[j + 1]);
            snprintf(temp2, 6, "%s%s", str_digits[j + 1], str_digits[j]);
            if (strcmp(temp1, temp2) <= 0) {
                char *t = str_digits[j];
                str_digits[j] = str_digits[j + 1];
                str_digits[j + 1] = t;
            }
        }
    }

    char *result = (char *)malloc((size * 2 + 1) * sizeof(char));
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
        strncat(result, str_digits[i], 3);
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