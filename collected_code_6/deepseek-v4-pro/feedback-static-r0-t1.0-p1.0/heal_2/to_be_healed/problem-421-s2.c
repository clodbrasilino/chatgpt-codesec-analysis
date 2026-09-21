#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concat_tuple(const char **tuple, size_t size, const char *delimiter) {
    if (tuple == NULL || delimiter == NULL || size == 0) {
        return NULL;
    }

    size_t delim_length = strnlen(delimiter, SIZE_MAX);
    size_t total_length = 0;
    size_t i;

    for (i = 0; i < size; i++) {
        if (tuple[i] == NULL) {
            return NULL;
        }
        total_length += strnlen(tuple[i], SIZE_MAX);
    }

    total_length += delim_length * (size - 1);

    if (total_length > SIZE_MAX - 1) {
        return NULL;
    }

    char *result = (char *)malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    result[0] = '\0';

    for (i = 0; i < size; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t remaining = total_length - strlen(result) + 1;
        /* Possible weaknesses found:
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         */
        strncat(result, tuple[i], remaining - 1);
        if (i < size - 1) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            remaining = total_length - strlen(result) + 1;
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
             */
            strncat(result, delimiter, remaining - 1);
        }
    }

    return result;
}

int main(void) {
    const char *tuple1[] = {"Hello", "World", "C"};
    const char *tuple2[] = {"apple", "banana", "cherry", "date"};
    const char *tuple3[] = {"single"};
    const char *empty_tuple[] = {""};
    const char *tuple_with_null[] = {"first", NULL, "third"};

    char *result = concat_tuple(tuple1, 3, "-");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = concat_tuple(tuple2, 4, ", ");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = concat_tuple(tuple3, 1, "|");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = concat_tuple(empty_tuple, 1, ";");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = concat_tuple(tuple_with_null, 3, "-");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        printf("NULL\n");
    }

    /* Possible weaknesses found:
     *  Assignment 'result=concat_tuple(NULL,3,"|")', assigned value is 0
     *  Calling function 'concat_tuple' returns 0
     */
    result = concat_tuple(NULL, 3, "|");
    /* Possible weaknesses found:
     *  Condition 'result!=NULL' is always false [knownConditionTrueFalse]
     *  Condition 'result!=NULL' is always false
     */
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        printf("NULL\n");
    }

    return 0;
}