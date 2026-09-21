#include <stdio.h>
#include <stdlib.h>

char* flatten_tuple_list(const char *list[], int size) {
    if (size <= 0) return NULL;

    int total_length = 0;
    for (int i = 0; i < size; ++i) {
        for (const char *p = list[i]; *p != '\0'; ++p) {
            total_length++;
        }
    }

    char *result = malloc(total_length + 1);
    if (result == NULL) return NULL;

    result[0] = '\0';
    size_t current_length = 0;
    for (int i = 0; i < size; ++i) {
        const char *src = list[i];
        while (*src != '\0') {
            if (current_length < total_length) {
                result[current_length++] = *src++;
            } else {
                free(result);
                return NULL;
            }
        }
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
    } else {
        fprintf(stderr, "Failed to flatten the tuple list.\n");
    }

    return 0;
}