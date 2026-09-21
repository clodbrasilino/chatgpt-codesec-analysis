#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static size_t safe_strlen(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

char *concat_tuple(const char **tuple, size_t size, const char *delimiter) {
    if (tuple == NULL || delimiter == NULL || size == 0) {
        return NULL;
    }

    size_t delim_length = safe_strlen(delimiter, SIZE_MAX);
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
        lengths[i] = safe_strlen(tuple[i], SIZE_MAX);
        if (lengths[i] > SIZE_MAX - total_length) {
            free(lengths);
            return NULL;
        }
        total_length += lengths[i];
        if (i < size - 1) {
            if (delim_length > SIZE_MAX - total_length) {
                free(lengths);
                return NULL;
            }
            total_length += delim_length;
        }
    }

    if (total_length == SIZE_MAX) {
        free(lengths);
        return NULL;
    }

    char *result = (char *)malloc(total_length + 1);
    if (result == NULL) {
        free(lengths);
        return NULL;
    }

    char *ptr = result;

    for (size_t i = 0; i < size; i++) {
        if (lengths[i] > 0) {
            if ((size_t)(ptr - result) + lengths[i] > total_length) {
                free(lengths);
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(ptr, tuple[i], lengths[i]);
            ptr += lengths[i];
        }
        if (i < size - 1) {
            if (delim_length > 0) {
                if ((size_t)(ptr - result) + delim_length > total_length) {
                    free(lengths);
                    free(result);
                    return NULL;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(ptr, delimiter, delim_length);
                ptr += delim_length;
            }
        }
    }
    *ptr = '\0';

    free(lengths);
    return result;
}

int main(void) {
    const char *tuple1[] = {"Hello", "World", "C"};
    const char *tuple2[] = {"one", "two", "three", "four"};
    const char *tuple3[] = {"single"};
    const char *tuple4[] = {"", "empty", ""};
    const char *tuple5[] = {"a", NULL, "b"};

    char *result1 = concat_tuple(tuple1, 3, "-");
    char *result2 = concat_tuple(tuple2, 4, ", ");
    char *result3 = concat_tuple(tuple3, 1, "|");
    char *result4 = concat_tuple(tuple4, 3, "::");
    char *result5 = concat_tuple(tuple5, 3, "+");
    /* Possible weaknesses found:
     *  Calling function 'concat_tuple' returns 0
     *  Assignment 'result6=concat_tuple(NULL,3,"-")', assigned value is 0
     */
    char *result6 = concat_tuple(NULL, 3, "-");
    char *result7 = concat_tuple(tuple1, 3, NULL);

    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1);
    }

    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }

    if (result3 != NULL) {
        printf("%s\n", result3);
        free(result3);
    }

    if (result4 != NULL) {
        printf("%s\n", result4);
        free(result4);
    }

    if (result5 != NULL) {
        printf("%s\n", result5);
        free(result5);
    }

    /* Possible weaknesses found:
     *  Condition 'result6!=NULL' is always false
     *  Condition 'result6!=NULL' is always false [knownConditionTrueFalse]
     */
    if (result6 != NULL) {
        printf("%s\n", result6);
        free(result6);
    }

    if (result7 != NULL) {
        printf("%s\n", result7);
        free(result7);
    }

    return 0;
}