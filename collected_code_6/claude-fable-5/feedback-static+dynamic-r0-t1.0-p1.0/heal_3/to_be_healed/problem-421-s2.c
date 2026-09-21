#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 4096

char *concatenate_tuple(const char **elements, size_t count, const char *delimiter)
{
    size_t total_length;
    size_t delimiter_length;
    size_t *element_lengths;
    size_t offset;
    size_t i;
    char *result;

    if (elements == NULL || delimiter == NULL || count == 0) {
        return NULL;
    }

    delimiter_length = strnlen(delimiter, MAX_STRING_LENGTH);
    if (delimiter_length == MAX_STRING_LENGTH && delimiter[MAX_STRING_LENGTH] != '\0') {
        return NULL;
    }

    element_lengths = malloc(count * sizeof(size_t));
    if (element_lengths == NULL) {
        return NULL;
    }

    total_length = 0;

    for (i = 0; i < count; i++) {
        if (elements[i] == NULL) {
            free(element_lengths);
            return NULL;
        }
        element_lengths[i] = strnlen(elements[i], MAX_STRING_LENGTH);
        if (element_lengths[i] == MAX_STRING_LENGTH && elements[i][MAX_STRING_LENGTH] != '\0') {
            free(element_lengths);
            return NULL;
        }
        if (element_lengths[i] > SIZE_MAX - total_length) {
            free(element_lengths);
            return NULL;
        }
        total_length += element_lengths[i];
        if (i < count - 1) {
            if (delimiter_length > SIZE_MAX - total_length) {
                free(element_lengths);
                return NULL;
            }
            total_length += delimiter_length;
        }
    }

    if (total_length == SIZE_MAX) {
        free(element_lengths);
        return NULL;
    }

    result = malloc(total_length + 1);
    if (result == NULL) {
        free(element_lengths);
        return NULL;
    }

    offset = 0;

    for (i = 0; i < count; i++) {
        if (element_lengths[i] > total_length - offset) {
            free(result);
            free(element_lengths);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + offset, elements[i], element_lengths[i]);
        offset += element_lengths[i];
        if (i < count - 1) {
            if (delimiter_length > total_length - offset) {
                free(result);
                free(element_lengths);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + offset, delimiter, delimiter_length);
            offset += delimiter_length;
        }
    }

    result[offset] = '\0';

    free(element_lengths);
    return result;
}

int main(void)
{
    const char *tuple[] = { "ID", "is", "4", "UTS" };
    size_t count = sizeof(tuple) / sizeof(tuple[0]);
    char *joined;

    joined = concatenate_tuple(tuple, count, "-");
    if (joined == NULL) {
        fprintf(stderr, "Error: concatenation failed\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", joined) < 0) {
        free(joined);
        return EXIT_FAILURE;
    }

    free(joined);
    return EXIT_SUCCESS;
}