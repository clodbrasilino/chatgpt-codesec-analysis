#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* remove_k_length_words(const char *str, int k) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *result = (char*)malloc(len + 1);
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
             * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
             */
            strcat(result, start);
            if (p < str + len && *p == ' ') {
                /* Possible weaknesses found:
                 * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). Risk is low because the source is a constant character. (risk 1, buffer)
                 */
                strcat(result, " ");
            }
        }
        p += (p < str + len && *p == ' ') ? 1 : 0;
    }

    return result;
}

int main() {
    /* Possible weaknesses found:
     *  Variable 'str' can be declared as const array [constVariable]
     */
    char str[] = "this is a test string with some words of length four and five";
    int k = 4;
    char *result = remove_k_length_words(str, k);
    if (result) {
        printf("%s\n", result);
        free(result);
    }
    return 0;
}