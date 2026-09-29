#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_list(const char *list[], size_t length) {
    if (length == 0) return NULL;

    size_t total_length = 0;
    for (size_t i = 0; i < length; ++i) {
        if (list[i] != NULL) {
            total_length += strnlen(list[i], 1024) + 1;
        }
    }

    char *result = (char *)malloc(total_length);
    if (result == NULL) return NULL;

    result[0] = '\0';
    for (size_t i = 0, pos = 0; i < length; ++i) {
        if (list[i] != NULL) {
            size_t len = strnlen(list[i], 1024);
            memmove(result + pos, list[i], len);
            pos += len;
            result[pos++] = ' ';
        }
    }
    /* Possible weaknesses found:
     *  use of undeclared identifier 'pos'
     *  'pos' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     */
    if (pos > 0) result[pos - 1] = '\0';

    return result;
}

int main() {
    const char *list[] = {"Hello", " ", "World", "!"};
    size_t length = sizeof(list) / sizeof(list[0]);

    char *concatenated = concatenate_list(list, length);
    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    return 0;
}