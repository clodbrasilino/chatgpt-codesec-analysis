#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* find_first_max_even_word(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char* buffer = (char*)malloc(len + 1);
    if (buffer == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(buffer, str, len + 1);
    buffer[len] = '\0';

    size_t max_len = 0;
    char* result = NULL;

    char* token = strtok(buffer, " \t\n\r");
    while (token != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t token_len = strlen(token);
        if (token_len % 2 == 0) {
            if (token_len > max_len) {
                max_len = token_len;
                if (result != NULL) {
                    free(result);
                }
                result = (char*)malloc(token_len + 1);
                if (result == NULL) {
                    free(buffer);
                    return NULL;
                }
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(result, token, token_len + 1);
            }
        }
        token = strtok(NULL, " \t\n\r");
    }

    free(buffer);
    return result;
}

int main(void) {
    const char* text = "This is a simple test string with some even and odd length words";
    char* max_even_word = find_first_max_even_word(text);

    if (max_even_word != NULL) {
        printf("First maximum length even word: %s\n", max_even_word);
        free(max_even_word);
    } else {
        printf("No even length word found.\n");
    }

    return 0;
}