#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char **elements;
    size_t count;
} Tuple;

char *tuple_join(const Tuple *tuple, const char *delimiter)
{
    size_t total_length;
    size_t delimiter_length;
    size_t i;
    char *result;
    char *current;

    if (tuple == NULL || delimiter == NULL) {
        return NULL;
    }

    if (tuple->count == 0 || tuple->elements == NULL) {
        result = malloc(1);
        if (result != NULL) {
            result[0] = '\0';
        }
        return result;
    }

    delimiter_length = strnlen(delimiter, 4096);
    if (delimiter_length == 4096) {
        return NULL;
    }

    total_length = 1;

    for (i = 0; i < tuple->count; i++) {
        size_t element_length;

        if (tuple->elements[i] == NULL) {
            return NULL;
        }

        element_length = strnlen(tuple->elements[i], 4096);
        if (element_length == 4096) {
            return NULL;
        }

        if (total_length > SIZE_MAX - element_length) {
            return NULL;
        }
        total_length += element_length;

        if (i > 0) {
            if (total_length > SIZE_MAX - delimiter_length) {
                return NULL;
            }
            total_length += delimiter_length;
        }
    }

    result = malloc(total_length);
    if (result == NULL) {
        return NULL;
    }

    current = result;
    for (i = 0; i < tuple->count; i++) {
        size_t element_length = strnlen(tuple->elements[i], 4096);
        size_t remaining = (size_t)(result + total_length - current);

        if (i > 0) {
            if (remaining < delimiter_length) {
                free(result);
                return NULL;
            }
            if (delimiter_length > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(current, delimiter, delimiter_length);
                current += delimiter_length;
                remaining -= delimiter_length;
            }
        }

        if (remaining < element_length) {
            free(result);
            return NULL;
        }
        if (element_length > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(current, tuple->elements[i], element_length);
            current += element_length;
        }
    }

    if ((size_t)(result + total_length - current) < 1) {
        free(result);
        return NULL;
    }
    *current = '\0';
    return result;
}

int main(void)
{
    char *data[] = {"apple", "banana", "cherry", "date"};
    Tuple tuple = {data, 4};
    char *joined;

    joined = tuple_join(&tuple, ", ");
    if (joined == NULL) {
        fprintf(stderr, "Failed to join tuple elements\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", joined);
    free(joined);

    return EXIT_SUCCESS;
}