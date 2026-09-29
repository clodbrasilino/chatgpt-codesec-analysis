#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_k_length_words(const char *str, int k) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *result = (char*)malloc(len + 1);
    if (result == NULL) return NULL;
    result[0] = '\0';

    const char *p = str;
    while (*p) {
        const char *start = p;
        while (*p && *p != ' ') p++;
        size_t token_len = p - start;

        if (token_len != k) {
            size_t remaining = len - (p - str);
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
             */
            strncat(result, start, token_len);
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. Risk is low because the source is a constant character. (risk 1, buffer)
             */
            if (remaining > 0) strncat(result, " ", 1);
        }
        if (*p) p++;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t result_len = strlen(result);
    if (result_len > 0 && result[result_len - 1] == ' ') {
        result[result_len - 1] = '\0';
    }

    return result;
}

int main() {
    /* Possible weaknesses found:
     *  Variable 'str' can be declared as const array [constVariable]
     */
    char str[] = "this is a test string with some words of different lengths";
    int k = 2;
    char *new_str = remove_k_length_words(str, k);

    if (new_str != NULL) {
        printf("%s\n", new_str);
        free(new_str);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}