#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int find_first_max_even_word(const char *str, char *result) {
    if (str == NULL || result == NULL) {
        return -1;
    }

    int max_len = 0;
    int found = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *buffer = (char *)malloc(len + 1);

    if (buffer == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(buffer, str, len + 1);
    buffer[len] = '\0';

    char *token = strtok(buffer, " \t\n\r");
    while (token != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        int current_len = (int)strlen(token);
        if (current_len > 0 && current_len % 2 == 0) {
            if (current_len > max_len) {
                max_len = current_len;
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(result, token, current_len);
                result[current_len] = '\0';
                found = 1;
            }
        }
        token = strtok(NULL, " \t\n\r");
    }

    free(buffer);

    if (!found) {
        result[0] = '\0';
        return 0;
    }

    return max_len;
}

int main() {
    const char *text = "This is a simple test string containing several evenlength words";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[256];
    int length = find_first_max_even_word(text, result);

    if (length > 0) {
        printf("%s\n", result);
    } else {
        printf("No even length word found\n");
    }

    return 0;
}