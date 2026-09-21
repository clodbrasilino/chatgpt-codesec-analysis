#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* flatten_tuple_list(const char *list[], int size) {
    if (size <= 0) return NULL;

    int total_length = 0;
    for (int i = 0; i < size; ++i) {
        if (list[i] == NULL) return NULL;
        size_t len = strlen(list[i]);
        total_length += (len + 1);
    }

    char *result = (char *)malloc(total_length);
    if (result == NULL) return NULL;

    result[0] = '\0';
    for (int i = 0; i < size; ++i) {
        strncat(result, list[i], total_length - strlen(result) - 1);
        if (i < size - 1) {
            strncat(result, " ", total_length - strlen(result) - 1);
        }
    }

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