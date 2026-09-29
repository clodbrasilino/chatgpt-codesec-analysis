#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CHAR_RANGE 256

int are_permutations(const char *str1, const char *str2) {
    int count[CHAR_RANGE] = {0};
    size_t len1, len2, i;

    if (str1 == NULL || str2 == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len1 = strlen(str1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len2 = strlen(str2);

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
    char str1[256];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str2[256];
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

    result = are_permutations(str1, str2);

    if (result) {
        printf("The strings are permutations of each other.\n");
    } else {
        printf("The strings are not permutations of each other.\n");
    }

    return EXIT_SUCCESS;
}