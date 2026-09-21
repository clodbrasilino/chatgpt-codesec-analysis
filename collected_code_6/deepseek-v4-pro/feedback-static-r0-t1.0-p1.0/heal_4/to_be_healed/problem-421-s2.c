#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *concat_tuple(const char **tuple, size_t size, const char *delimiter) {
    if (tuple == NULL || delimiter == NULL || size == 0) {
        return NULL;
    }

    size_t delim_length = 0;
    const char *d = delimiter;
    while (*d != '\0') {
        delim_length++;
        d++;
    }

    size_t total_length = 0;
    for (size_t i = 0; i < size; i++) {
        if (tuple[i] == NULL) {
            return NULL;
        }
        const char *s = tuple[i];
        while (*s != '\0') {
            total_length++;
            s++;
        }
    }

    if (size > 1) {
        if (delim_length > SIZE_MAX / (size - 1)) {
            return NULL;
        }
        if (total_length > SIZE_MAX - delim_length * (size - 1)) {
            return NULL;
        }
        total_length += delim_length * (size - 1);
    }

    if (total_length > SIZE_MAX - 1) {
        return NULL;
    }

    char *result = (char *)malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t offset = 0;
    for (size_t i = 0; i < size; i++) {
        const char *s = tuple[i];
        size_t len = 0;
        while (s[len] != '\0') {
            len++;
        }
        if (offset + len > total_length) {
            free(result);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + offset, s, len);
        offset += len;

        if (i < size - 1) {
            if (offset + delim_length > total_length) {
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + offset, delimiter, delim_length);
            offset += delim_length;
        }
    }

    result[offset] = '\0';
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