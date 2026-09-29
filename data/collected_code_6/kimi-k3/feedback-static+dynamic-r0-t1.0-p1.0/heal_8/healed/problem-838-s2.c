#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 1000

int minSwaps(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return -1;
    }

    size_t len1 = strnlen(str1, MAX_LEN + 1);
    size_t len2 = strnlen(str2, MAX_LEN + 1);

    if (len1 > MAX_LEN || len2 > MAX_LEN) {
        return -1;
    }

    if (len1 != len2) {
        return -1;
    }

    int count1 = 0;
    int count2 = 0;

    for (size_t i = 0; i < len1; i++) {
        if ((str1[i] != '0' && str1[i] != '1') ||
            (str2[i] != '0' && str2[i] != '1')) {
            return -1;
        }

        if (str1[i] == '1') {
            count1++;
        }
        if (str2[i] == '1') {
            count2++;
        }
    }

    if (count1 != count2) {
        return -1;
    }

    int mismatch01 = 0;
    int mismatch10 = 0;

    for (size_t i = 0; i < len1; i++) {
        if (str1[i] != str2[i]) {
            if (str1[i] == '0') {
                mismatch01++;
            } else {
                mismatch10++;
            }
        }
    }

    return (mismatch01 > mismatch10) ? mismatch01 : mismatch10;
}

int main(void) {
    char *str1 = malloc(MAX_LEN + 2);
    char *str2 = malloc(MAX_LEN + 2);

    if (str1 == NULL || str2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(str1);
        free(str2);
        return EXIT_FAILURE;
    }

    if (fgets(str1, MAX_LEN + 2, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(str1);
        free(str2);
        return EXIT_FAILURE;
    }

    if (fgets(str2, MAX_LEN + 2, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(str1);
        free(str2);
        return EXIT_FAILURE;
    }

    str1[strcspn(str1, "\n")] = '\0';
    str2[strcspn(str2, "\n")] = '\0';

    int result = minSwaps(str1, str2);

    if (result == -1) {
        printf("Cannot make strings equal (invalid input or different number of 1s)\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }

    free(str1);
    free(str2);

    return EXIT_SUCCESS;
}