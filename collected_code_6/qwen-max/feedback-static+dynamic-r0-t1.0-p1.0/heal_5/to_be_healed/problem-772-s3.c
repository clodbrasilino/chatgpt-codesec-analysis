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

    const char *src = str;
    char *dest = result;

    while (*src) {
        const char *start = src;
        while (*src && *src != ' ') src++;
        size_t word_len = src - start;

        if (word_len != k) {
            size_t space_left = len + 1 - (dest - result);
            if (word_len < space_left) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(dest, start, word_len);
                dest += word_len;
            }
            if (src < str + len && *(src + 1)) {
                *dest++ = ' ';
            }
        }
        if (*src) src++;
    }

    *dest = '\0';
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