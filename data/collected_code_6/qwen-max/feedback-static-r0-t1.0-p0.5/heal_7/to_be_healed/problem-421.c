#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concat_with_delimiter(const char *tuple[], size_t tuple_size, const char *delimiter) {
    if (tuple_size == 0) return NULL;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t delimiter_len = delimiter ? strlen(delimiter) : 0;
    size_t total_len = 0;
    for (size_t i = 0; i < tuple_size; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (tuple[i]) total_len += strlen(tuple[i]);
    }
    total_len += (tuple_size - 1) * delimiter_len + 1;

    char *result = (char *)malloc(total_len * sizeof(char));
    if (result == NULL) return NULL;

    result[0] = '\0';
    size_t pos = 0;
    for (size_t i = 0; i < tuple_size; ++i) {
        if (tuple[i] != NULL) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(tuple[i]);
            memmove(result + pos, tuple[i], len);
            pos += len;
        }
        if (i < tuple_size - 1 && delimiter) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(delimiter);
            memmove(result + pos, delimiter, len);
            pos += len;
        }
    }
    result[pos] = '\0';

    return result;
}

int main() {
    const char *tuple[] = {"apple", "banana", "cherry"};
    size_t tuple_size = 3;
    const char *delimiter = ",";

    char *result = concat_with_delimiter(tuple, tuple_size, delimiter);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    return 0;
}