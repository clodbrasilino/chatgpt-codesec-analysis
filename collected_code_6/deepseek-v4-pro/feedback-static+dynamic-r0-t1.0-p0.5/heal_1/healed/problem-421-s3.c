#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concat_tuple(char **tuple, size_t size, const char *delimiter) {
    if (tuple == NULL || delimiter == NULL) {
        return NULL;
    }

    if (size == 0) {
        char *result = (char *)malloc(1);
        if (result != NULL) {
            result[0] = '\0';
        }
        return result;
    }

    size_t delim_length = delimiter ? strlen(delimiter) : 0;
    size_t *lengths = (size_t *)malloc(size * sizeof(size_t));
    if (lengths == NULL) {
        return NULL;
    }

    size_t total_length = 0;
    for (size_t i = 0; i < size; i++) {
        if (tuple[i] == NULL) {
            free(lengths);
            return NULL;
        }
        lengths[i] = strlen(tuple[i]);
        total_length += lengths[i];
        if (i < size - 1) {
            total_length += delim_length;
        }
    }

    char *result = (char *)malloc(total_length + 1);
    if (result == NULL) {
        free(lengths);
        return NULL;
    }

    char *dest = result;
    for (size_t i = 0; i < size; i++) {
        memcpy(dest, tuple[i], lengths[i]);
        dest += lengths[i];
        if (i < size - 1) {
            memcpy(dest, delimiter, delim_length);
            dest += delim_length;
        }
    }
    *dest = '\0';

    free(lengths);
    return result;
}

int main(void) {
    char *tuple1[] = {"Hello", "World", "C"};
    char *tuple2[] = {"apple", "banana", "cherry", "date"};
    char *tuple3[] = {"single"};
    char *tuple4[] = {"", "empty", "", "strings"};
    char *tuple5[] = {"no_delimiter"};

    char *result1 = concat_tuple(tuple1, 3, "-");
    char *result2 = concat_tuple(tuple2, 4, ", ");
    char *result3 = concat_tuple(tuple3, 1, "|");
    char *result4 = concat_tuple(tuple4, 4, "::");
    char *result5 = concat_tuple(tuple5, 1, ";");
    char *result6 = concat_tuple(NULL, 3, "-");
    char *result7 = concat_tuple(tuple1, 3, NULL);

    printf("Result 1: %s\n", result1 ? result1 : "(null)");
    printf("Result 2: %s\n", result2 ? result2 : "(null)");
    printf("Result 3: %s\n", result3 ? result3 : "(null)");
    printf("Result 4: %s\n", result4 ? result4 : "(null)");
    printf("Result 5: %s\n", result5 ? result5 : "(null)");
    printf("Result 6: %s\n", result6 ? result6 : "(null)");
    printf("Result 7: %s\n", result7 ? result7 : "(null)");

    free(result1);
    free(result2);
    free(result3);
    free(result4);
    free(result5);
    free(result6);
    free(result7);

    return 0;
}