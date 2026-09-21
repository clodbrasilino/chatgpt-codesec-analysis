#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int find_first_max_even_word(const char *str, char *result, size_t result_size) {
    if (str == NULL || result == NULL || result_size == 0) {
        return -1;
    }

    int max_len = 0;
    int found = 0;
    size_t len = strnlen(str, SIZE_MAX);
    
    char *buffer = (char *)malloc(len + 1);
    if (buffer == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, str, len + 1);

    const char *delim = " \t\n\r";
    char *saveptr = NULL;
    char *token = strtok_r(buffer, delim, &saveptr);
    
    while (token != NULL) {
        size_t current_len = strnlen(token, len + 1);
        if (current_len > 0 && current_len % 2 == 0) {
            if (current_len > (size_t)max_len) {
                max_len = (int)current_len;
                size_t copy_len = current_len < result_size - 1 ? current_len : result_size - 1;
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result, token, copy_len);
                result[copy_len] = '\0';
                found = 1;
            }
        }
        token = strtok_r(NULL, delim, &saveptr);
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
    size_t result_size = 256;
    char *result = (char *)malloc(result_size);
    if (result == NULL) {
        return 1;
    }

    int length = find_first_max_even_word(text, result, result_size);

    if (length > 0) {
        printf("%s\n", result);
    } else {
        printf("No even length word found\n");
    }

    free(result);
    return 0;
}