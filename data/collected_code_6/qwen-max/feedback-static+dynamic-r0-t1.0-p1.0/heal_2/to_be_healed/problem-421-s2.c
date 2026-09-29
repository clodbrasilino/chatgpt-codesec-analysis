#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_with_delimiter(const char* tuple[], size_t length, const char* delimiter) {
    if (length == 0) return NULL;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t delimiter_length = strlen(delimiter);
    size_t total_length = 0;
    for (size_t i = 0; i < length; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        total_length += strlen(tuple[i]);
    }
    total_length += delimiter_length * (length - 1);

    char* result = (char*)malloc(total_length + 1);
    if (result == NULL) return NULL;
    result[0] = '\0';

    for (size_t i = 0; i < length; ++i) {
        if (i > 0) {
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
             */
            strncat(result, delimiter, delimiter_length);
        }
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         */
        strncat(result, tuple[i], total_length - strlen(result));
    }

    return result;
}

void free_concatenated_string(char* str) {
    if (str != NULL) {
        free(str);
    }
}

int main() {
    const char* tuple[] = {"Hello", "World", "C", "Programming"};
    size_t length = sizeof(tuple) / sizeof(tuple[0]);
    const char* delimiter = "-";

    char* result = concatenate_with_delimiter(tuple, length, delimiter);
    if (result != NULL) {
        printf("%s\n", result);
        free_concatenated_string(result);
    } else {
        fprintf(stderr, "Memory allocation failed.\n");
    }

    return 0;
}