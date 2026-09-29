#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>

#define CHAR_RANGE (UCHAR_MAX + 1)
#define BUFFER_SIZE 256

int are_permutations(const char *str1, const char *str2, size_t max_len) {
    int count[CHAR_RANGE] = {0};
    size_t len1, len2, i;

    if (str1 == NULL || str2 == NULL || max_len == 0) {
        return 0;
    }

    len1 = strnlen(str1, max_len);
    len2 = strnlen(str2, max_len);

    if (len1 == max_len || len2 == max_len) {
        return 0;
    }

    if (len1 != len2) {
        return 0;
    }

    for (i = 0; i < len1; i++) {
        count[(unsigned char)str1[i]]++;
        count[(unsigned char)str2[i]]--;
    }

    for (i = 0; i < CHAR_RANGE; i++) {
        if (count[i] != 0) {
            return 0;
        }
    }

    return 1;
}

int main(void) {
    char *str1 = NULL;
    char *str2 = NULL;
    size_t str1_capacity = 0;
    size_t str2_capacity = 0;
    ssize_t len1, len2;
    int result;

    printf("Enter first string: ");
    len1 = getline(&str1, &str1_capacity, stdin);
    if (len1 == -1) {
        fprintf(stderr, "Error reading input\n");
        free(str1);
        return EXIT_FAILURE;
    }

    if (len1 > 0 && str1[len1 - 1] == '\n') {
        str1[len1 - 1] = '\0';
        len1--;
    }

    printf("Enter second string: ");
    len2 = getline(&str2, &str2_capacity, stdin);
    if (len2 == -1) {
        fprintf(stderr, "Error reading input\n");
        free(str1);
        free(str2);
        return EXIT_FAILURE;
    }

    if (len2 > 0 && str2[len2 - 1] == '\n') {
        str2[len2 - 1] = '\0';
        len2--;
    }

    result = are_permutations(str1, str2, (size_t)(len1 + 1));

    if (result) {
        printf("The strings are permutations of each other.\n");
    } else {
        printf("The strings are not permutations of each other.\n");
    }

    free(str1);
    free(str2);

    return EXIT_SUCCESS;
}