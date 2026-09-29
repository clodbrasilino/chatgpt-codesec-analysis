#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concat_tuple(char **tuple, size_t size, const char *delimiter) {
    if (tuple == NULL || delimiter == NULL) {
        return NULL;
    }

    if (size == 0) {
        char *empty = (char *)malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    for (size_t i = 0; i < size; i++) {
        if (tuple[i] == NULL) {
            return NULL;
        }
    }

    size_t total_length = 0;
    size_t delim_length = strlen(delimiter);

    for (size_t i = 0; i < size; i++) {
        total_length += strlen(tuple[i]);
        if (i < size - 1) {
            total_length += delim_length;
        }
    }

    char *result = (char *)malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    result[0] = '\0';

    for (size_t i = 0; i < size; i++) {
        strcat(result, tuple[i]);
        if (i < size - 1) {
            strcat(result, delimiter);
        }
    }

    return result;
}

int main(void) {
    char *tuple1[] = {"Hello", "World", "C"};
    char *tuple2[] = {"one", "two", "three", "four"};
    char *tuple3[] = {"single"};
    char *empty_tuple[] = {};

    char *result1 = concat_tuple(tuple1, 3, "-");
    char *result2 = concat_tuple(tuple2, 4, ", ");
    char *result3 = concat_tuple(tuple3, 1, "|");
    char *result4 = concat_tuple(empty_tuple, 0, ",");
    char *result5 = concat_tuple(NULL, 3, "-");
    char *result6 = concat_tuple(tuple1, 3, NULL);

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

    if (result6 != NULL) {
        printf("%s\n", result6);
        free(result6);
    }

    return 0;
}