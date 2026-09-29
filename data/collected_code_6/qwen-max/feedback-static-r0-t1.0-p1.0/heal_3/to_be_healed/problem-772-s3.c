#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* remove_k_length_words(const char *str, int k) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *result = malloc(len + 1);
    if (!result) return NULL;
    result[0] = '\0';

    const char *p = str;
    while (*p) {
        const char *start = p;
        while (*p && *p != ' ') p++;
        size_t word_len = p - start;
        if (word_len != k) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t new_len = strlen(result) + word_len + (p < str + len ? 1 : 0);
            if (new_len > len + 1) {
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
             */
            strncat(result, start, word_len);
            if (p < str + len && *p == ' ') {
                /* Possible weaknesses found:
                 * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. Risk is low because the source is a constant character. (risk 1, buffer)
                 */
                strncat(result, " ", 1);
            }
        }
        p += (p < str + len && *p == ' ') ? 1 : 0;
    }

    return result;
}

int main() {
    const char str[] = "this is a test string with some words of length four and five";
    int k = 4;
    char *result = remove_k_length_words(str, k);
    if (result) {
        printf("%s\n", result);
        free(result);
    }
    return 0;
}