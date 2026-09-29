#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int are_permutations(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL || !(*str1 && *str2)) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len1 = strlen(str1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len2 = strlen(str2);
    if (str_len1 != str_len2) {
        return 0;
    }
    int *count = (int *)calloc(256, sizeof(int));
    if (count == NULL) {
        return -1;
    }
    for (size_t i = 0; i < str_len1; i++) {
        count[(unsigned char)str1[i]]++;
        count[(unsigned char)str2[i]]--;
    }
    for (size_t i = 0; i < 256; i++) {
        if (count[i] != 0) {
            free(count);
            return 0;
        }
    }
    free(count);
    return 1;
}

int main() {
    const char *str1 = "test";
    const char *str2 = "ttew";
    int result = are_permutations(str1, str2);
    if (result == 1) {
        printf("The strings are permutations of each other.\n");
    } else if (result == 0) {
        printf("The strings are not permutations of each other.\n");
    } else {
        printf("Memory allocation failed or input is invalid.\n");
    }
    return 0;
}