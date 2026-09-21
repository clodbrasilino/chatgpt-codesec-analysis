#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static size_t safe_strlen(const char *str, size_t max_len) {
    if (str == NULL) {
        return SIZE_MAX;
    }
    for (size_t i = 0; i < max_len; i++) {
        if (str[i] == '\0') {
            return i;
        }
    }
    return SIZE_MAX;
}

char *concat_tuple(const char **tuple, size_t size, const char *delimiter) {
    if (tuple == NULL || delimiter == NULL || size == 0) {
        return NULL;
    }

    size_t delim_length = safe_strlen(delimiter, SIZE_MAX);
    if (delim_length == SIZE_MAX) {
        return NULL;
    }

    size_t total_length = 0;
    size_t *lengths = (size_t *)malloc(size * sizeof(size_t));
    if (lengths == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        if (tuple[i] == NULL) {
            free(lengths);
            return NULL;
        }

        size_t len = safe_strlen(tuple[i], SIZE_MAX - total_length);
        if (len == SIZE_MAX) {
            free(lengths);
            return NULL;
        }
        lengths[i] = len;

        if (total_length > SIZE_MAX - len) {
            free(lengths);
            return NULL;
        }
        total_length += len;
    }

    if (size > 1) {
        if (delim_length > 0 && delim_length > SIZE_MAX / (size - 1)) {
            free(lengths);
            return NULL;
        }
        size_t delim_total = delim_length * (size - 1);
        if (total_length > SIZE_MAX - delim_total) {
            free(lengths);
            return NULL;
        }
        total_length += delim_total;
    }

    if (total_length > SIZE_MAX - 1) {
        free(lengths);
        return NULL;
    }

    char *result = (char *)malloc(total_length + 1);
    if (result == NULL) {
        free(lengths);
        return NULL;
    }

    size_t offset = 0;
    for (size_t i = 0; i < size; i++) {
        const char *s = tuple[i];
        size_t len = lengths[i];

        if (offset > total_length || len > total_length - offset) {
            free(result);
            free(lengths);
            return NULL;
        }

        memmove(result + offset, s, len);
        offset += len;

        if (i < size - 1) {
            if (offset > total_length || delim_length > total_length - offset) {
                free(result);
                free(lengths);
                return NULL;
            }

            memmove(result + offset, delimiter, delim_length);
            offset += delim_length;
        }
    }

    result[offset] = '\0';
    free(lengths);
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