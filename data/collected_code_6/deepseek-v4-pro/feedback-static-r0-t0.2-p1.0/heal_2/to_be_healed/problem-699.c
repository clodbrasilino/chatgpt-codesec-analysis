#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

int min_swaps_to_convert(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) {
        return -1;
    }

    size_t len1 = strnlen(s1, 1001);
    size_t len2 = strnlen(s2, 1001);

    if (len1 != len2 || len1 == 0 || len1 >= 1001) {
        return -1;
    }

    int count1 = 0, count2 = 0;
    int mismatch_positions = 0;
    int ones_in_mismatch = 0;

    for (size_t i = 0; i < len1; i++) {
        if (s1[i] != '0' && s1[i] != '1') {
            return -1;
        }
        if (s2[i] != '0' && s2[i] != '1') {
            return -1;
        }

        if (s1[i] == '1') count1++;
        if (s2[i] == '1') count2++;

        if (s1[i] != s2[i]) {
            mismatch_positions++;
            if (s1[i] == '1') {
                ones_in_mismatch++;
            }
        }
    }

    if (count1 != count2) {
        return -1;
    }

    return ones_in_mismatch;
}

int main(void) {
    char *str1 = NULL;
    char *str2 = NULL;
    size_t bufsize = 1002;
    ssize_t len1, len2;

    str1 = (char *)malloc(bufsize * sizeof(char));
    str2 = (char *)malloc(bufsize * sizeof(char));
    
    if (str1 == NULL || str2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(str1);
        free(str2);
        return 1;
    }

    printf("Enter first binary string: ");
    if (fgets(str1, bufsize, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(str1);
        free(str2);
        return 1;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len1 = strlen(str1);
    if (len1 > 0 && str1[len1 - 1] == '\n') {
        str1[len1 - 1] = '\0';
        len1--;
    }

    printf("Enter second binary string: ");
    if (fgets(str2, bufsize, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(str1);
        free(str2);
        return 1;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len2 = strlen(str2);
    if (len2 > 0 && str2[len2 - 1] == '\n') {
        str2[len2 - 1] = '\0';
        len2--;
    }

    if (len1 >= 1001 || len2 >= 1001) {
        fprintf(stderr, "Input exceeds maximum allowed length\n");
        free(str1);
        free(str2);
        return 1;
    }

    int result = min_swaps_to_convert(str1, str2);

    if (result == -1) {
        printf("Conversion not possible\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }

    free(str1);
    free(str2);
    return 0;
}