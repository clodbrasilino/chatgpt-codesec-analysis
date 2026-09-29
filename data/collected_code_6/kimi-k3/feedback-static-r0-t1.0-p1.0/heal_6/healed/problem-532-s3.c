#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

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
    char str1[BUFFER_SIZE];
    char str2[BUFFER_SIZE];
    int result;
    size_t len1, len2;
    int c;

    printf("Enter first string: ");
    if (fgets(str1, sizeof(str1), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len1 = strnlen(str1, sizeof(str1));
    if (len1 > 0 && str1[len1 - 1] == '\n') {
        str1[len1 - 1] = '\0';
    } else if (len1 == sizeof(str1) - 1 && !feof(stdin)) {
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    printf("Enter second string: ");
    if (fgets(str2, sizeof(str2), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len2 = strnlen(str2, sizeof(str2));
    if (len2 > 0 && str2[len2 - 1] == '\n') {
        str2[len2 - 1] = '\0';
    } else if (len2 == sizeof(str2) - 1 && !feof(stdin)) {
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    result = are_permutations(str1, str2, sizeof(str1));

    if (result) {
        printf("The strings are permutations of each other.\n");
    } else {
        printf("The strings are not permutations of each other.\n");
    }

    return EXIT_SUCCESS;
}