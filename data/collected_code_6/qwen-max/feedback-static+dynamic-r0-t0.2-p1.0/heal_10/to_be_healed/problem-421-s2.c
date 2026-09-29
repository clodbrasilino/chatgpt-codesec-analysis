#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_tuples(const char *tuple[], size_t tuple_size, const char *delimiter) {
    if (tuple == NULL || delimiter == NULL) return NULL;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t delimiter_len = strlen(delimiter);
    size_t total_len = 0;
    for (size_t i = 0; i < tuple_size; ++i) {
        total_len += strnlen(tuple[i], 1024);
    }
    total_len += (tuple_size - 1) * delimiter_len + 1;

    char *result = (char *)malloc(total_len * sizeof(char));
    if (result == NULL) return NULL;

    result[0] = '\0';
    size_t current_pos = 0;
    for (size_t i = 0; i < tuple_size; ++i) {
        size_t len = strnlen(tuple[i], 1024);
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(result + current_pos, tuple[i], len);
        result[current_pos + len] = '\0';
        current_pos += len;
        if (i < tuple_size - 1) {
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(result + current_pos, delimiter, delimiter_len);
            result[current_pos + delimiter_len] = '\0';
            current_pos += delimiter_len;
        }
    }

    return result;
}

int main() {
    const char *tuple[] = {"Hello", "World", "C"};
    size_t tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    const char *delimiter = ", ";

    char *result = concatenate_tuples(tuple, tuple_size, delimiter);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Failed to concatenate tuples.\n");
    }

    return 0;
}