#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* flatten_tuple_list(const char *list[], int size) {
    if (size <= 0) return NULL;

    int total_length = 0;
    for (int i = 0; i < size; ++i) {
        const char *item = list[i];
        if (item == NULL) return NULL;
        total_length += (int)strnlen(item, 1024);
    }
    char *result = (char *)malloc(total_length + 1);
    if (result == NULL) return NULL;

    result[0] = '\0';
    size_t current_length = 0;
    for (int i = 0; i < size; ++i) {
        const char *item = list[i];
        if (item == NULL) return NULL;
        size_t len = (int)strnlen(item, 1024);
        if (current_length + len > total_length) {
            free(result);
            return NULL;
        }
        memcpy(result + current_length, item, len);
        current_length += len;
    }
    result[total_length] = '\0';
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