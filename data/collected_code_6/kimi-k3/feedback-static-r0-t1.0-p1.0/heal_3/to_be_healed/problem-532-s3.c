#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CHAR_RANGE 256
#define BUFFER_SIZE 256

int are_permutations(const char *str1, const char *str2, size_t max_len) {
    int count[CHAR_RANGE] = {0};
    size_t len1, len2, i;

    if (str1 == NULL || str2 == NULL) {
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str1[BUFFER_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str2[BUFFER_SIZE];
    int result;

    printf("Enter first string: ");
    if (fgets(str1, sizeof(str1), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    printf("Enter second string: ");
    if (fgets(str2, sizeof(str2), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    str1[strcspn(str1, "\n")] = '\0';
    str2[strcspn(str2, "\n")] = '\0';

    result = are_permutations(str1, str2, sizeof(str1));

    if (result) {
        printf("The strings are permutations of each other.\n");
    } else {
        printf("The strings are not permutations of each other.\n");
    }

    return EXIT_SUCCESS;
}