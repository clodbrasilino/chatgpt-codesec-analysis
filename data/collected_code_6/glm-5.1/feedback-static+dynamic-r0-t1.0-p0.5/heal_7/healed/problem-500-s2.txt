#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concatenate_list(char **list, size_t size) {
    size_t total_length = 1;
    for (size_t i = 0; i < size; i++) {
        if (list[i] != NULL) {
            size_t len = strnlen(list[i], SIZE_MAX);
            if (len == SIZE_MAX) {
                return NULL;
            }
            total_length += len;
        }
    }

    char *result = malloc(total_length);
    if (result == NULL) {
        return NULL;
    }

    size_t current_pos = 0;
    for (size_t i = 0; i < size; i++) {
        if (list[i] != NULL) {
            size_t len = strnlen(list[i], total_length - current_pos);
            memcpy(result + current_pos, list[i], len);
            current_pos += len;
        }
    }

    result[current_pos] = '\0';

    return result;
}

int main(void) {
    char *list[] = {"Hello", " ", "World", "!"};
    size_t size = sizeof(list) / sizeof(list[0]);

    char *concatenated = concatenate_list(list, size);
    if (concatenated == NULL) {
        return EXIT_FAILURE;
    }

    printf("%s\n", concatenated);

    free(concatenated);
    concatenated = NULL;

    return EXIT_SUCCESS;
}