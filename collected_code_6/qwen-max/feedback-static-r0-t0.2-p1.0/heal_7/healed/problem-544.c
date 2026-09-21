#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* flatten_tuple_list(const char *list[], int size) {
    if (size <= 0) return NULL;

    int total_length = 0;
    for (int i = 0; i < size; ++i) {
        if (list[i] == NULL) return NULL;
        size_t len = strlen(list[i]);
        total_length += (len + 2);
    }

    char *result = (char *)malloc(total_length + 1);
    if (result == NULL) return NULL;

    result[0] = '\0';
    for (int i = 0, pos = 0; i < size; ++i) {
        size_t len = strlen(list[i]);
        strncpy(result + pos, list[i], len);
        pos += len;
        if (i < size - 1) {
            result[pos++] = ' ';
        }
    }
    result[total_length - 1] = '\0';

    return result;
}

int main() {
    const char *tuple_list[] = {"(1,2)", "(3,4)", "(5,6)"};
    int size = 3;
    char *flattened = flatten_tuple_list(tuple_list, size);
    if (flattened != NULL) {
        printf("%s\n", flattened);
        free(flattened);
    }
    return 0;
}