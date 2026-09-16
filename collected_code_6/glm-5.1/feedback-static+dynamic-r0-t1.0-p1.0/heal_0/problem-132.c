#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *tuple_to_string(int *tuple, size_t size) {
    if (tuple == NULL && size > 0) {
        return NULL;
    }

    size_t buffer_size = 4;
    for (size_t i = 0; i < size; i++) {
        int n = snprintf(NULL, 0, "%d", tuple[i]);
        if (n < 0) {
            return NULL;
        }
        buffer_size += (size_t)n;
        if (i < size - 1) {
            buffer_size += 2;
        }
    }

    char *str = (char *)malloc(buffer_size);
    if (str == NULL) {
        return NULL;
    }

    size_t pos = 0;
    str[pos++] = '(';

    for (size_t i = 0; i < size; i++) {
        int n = snprintf(str + pos, buffer_size - pos, "%d", tuple[i]);
        if (n < 0) {
            free(str);
            return NULL;
        }
        pos += (size_t)n;

        if (i < size - 1) {
            str[pos++] = ',';
            str[pos++] = ' ';
        }
    }

    if (buffer_size - pos < 2) {
        free(str);
        return NULL;
    }
    str[pos++] = ')';
    str[pos] = '\0';

    return str;
}

int main(void) {
    int tuple1[] = {1, 2, 3, 4, 5};
    size_t size1 = sizeof(tuple1) / sizeof(tuple1[0]);

    char *str1 = tuple_to_string(tuple1, size1);
    if (str1 == NULL) {
        return EXIT_FAILURE;
    }
    printf("%s\n", str1);
    free(str1);

    int tuple2[] = {10};
    size_t size2 = sizeof(tuple2) / sizeof(tuple2[0]);

    char *str2 = tuple_to_string(tuple2, size2);
    if (str2 == NULL) {
        return EXIT_FAILURE;
    }
    printf("%s\n", str2);
    free(str2);

    char *str3 = tuple_to_string(NULL, 0);
    if (str3 == NULL) {
        return EXIT_FAILURE;
    }
    printf("%s\n", str3);
    free(str3);

    return EXIT_SUCCESS;
}