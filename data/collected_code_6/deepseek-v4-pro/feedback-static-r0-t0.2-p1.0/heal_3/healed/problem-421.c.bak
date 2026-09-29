#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concat_tuple(const char **tuple, size_t size, const char *delimiter) {
    if (tuple == NULL || delimiter == NULL) {
        return NULL;
    }

    size_t total_length = 0;
    size_t delim_length = strlen(delimiter);

    for (size_t i = 0; i < size; i++) {
        if (tuple[i] == NULL) {
            return NULL;
        }
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
    const char *tuple1[] = {"Hello", "World", "C"};
    const char *tuple2[] = {"one", "two", "three", "four"};
    const char *tuple3[] = {"single"};
    const char *tuple4[] = {"", "empty", ""};
    const char *tuple5[] = {"a", NULL, "b"};

    char *result1 = concat_tuple(tuple1, 3, "-");
    char *result2 = concat_tuple(tuple2, 4, ", ");
    char *result3 = concat_tuple(tuple3, 1, "|");
    char *result4 = concat_tuple(tuple4, 3, "::");
    const char *result5 = concat_tuple(tuple5, 3, "+");
    const char *result6 = concat_tuple(NULL, 3, "-");
    const char *result7 = concat_tuple(tuple1, 3, NULL);

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

    if (result5 == NULL) {
        printf("NULL\n");
    }

    if (result6 == NULL) {
        printf("NULL\n");
    }

    if (result7 == NULL) {
        printf("NULL\n");
    }

    return 0;
}