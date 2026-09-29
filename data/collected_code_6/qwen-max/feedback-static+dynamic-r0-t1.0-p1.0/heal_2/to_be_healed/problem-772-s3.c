#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* remove_k_length_words(const char *str, int k) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    char *result = (char*)malloc(len + 1);
    if (!result) return NULL;
    result[0] = '\0';
    
    const char *src = str;
    while (*src) {
        int start = src - str;
        while (*src && *src != ' ') src++;
        int word_len = src - (str + start);
        if (word_len != k) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            if (strlen(result) + word_len + (src < str + len ? 1 : 0) < len + 1) {
                /* Possible weaknesses found:
                 * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
                 */
                strncat(result, str + start, word_len);
                if (src < str + len) {
                    /* Possible weaknesses found:
                     * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. Risk is low because the source is a constant character. (risk 1, buffer)
                     */
                    strncat(result, " ", 1);
                }
            }
        }
        if (*src) src++;
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