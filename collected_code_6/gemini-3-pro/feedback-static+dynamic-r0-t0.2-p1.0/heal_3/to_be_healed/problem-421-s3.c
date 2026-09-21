#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_tuple(const char** tuple, size_t tuple_size, const char* delimiter) {
    if (!tuple || !delimiter || tuple_size == 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t delimiter_length = strlen(delimiter);
    size_t total_length = 0;
    
    size_t* lengths = (size_t*)malloc(tuple_size * sizeof(size_t));
    if (!lengths) {
        return NULL;
    }

    for (size_t i = 0; i < tuple_size; ++i) {
        if (tuple[i]) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            lengths[i] = strlen(tuple[i]);
            total_length += lengths[i];
        } else {
            lengths[i] = 0;
        }
    }

    total_length += delimiter_length * (tuple_size - 1) + 1;

    char* result = (char*)malloc(total_length);
    if (!result) {
        free(lengths);
        return NULL;
    }

    result[0] = '\0';
    size_t current_len = 0;

    for (size_t i = 0; i < tuple_size; ++i) {
        if (tuple[i] && lengths[i] > 0) {
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
             */
            strncat(result + current_len, tuple[i], total_length - current_len - 1);
            current_len += lengths[i];
        }
        if (i < tuple_size - 1 && delimiter_length > 0) {
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
             */
            strncat(result + current_len, delimiter, total_length - current_len - 1);
            current_len += delimiter_length;
        }
    }

    free(lengths);
    return result;
}

int main(void) {
    const char* tuple[] = {"apple", "banana", "cherry", "date"};
    size_t tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    const char* delimiter = ", ";

    char* concatenated_string = concatenate_tuple(tuple, tuple_size, delimiter);

    if (concatenated_string) {
        printf("%s\n", concatenated_string);
        free(concatenated_string);
    } else {
        fprintf(stderr, "Failed to concatenate tuple.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}