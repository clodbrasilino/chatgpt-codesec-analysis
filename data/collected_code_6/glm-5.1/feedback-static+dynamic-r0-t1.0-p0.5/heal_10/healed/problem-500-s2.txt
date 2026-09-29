#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concatenate_list(char **list, size_t size) {
    size_t total_length = 1;
    for (size_t i = 0; i < size; i++) {
        if (list[i] != NULL) {
            size_t len = strlen(list[i]);
            size_t prev_length = total_length;
            total_length += len;
            if (total_length < prev_length) {
                return NULL;
            }
        }
    }

    char *result = malloc(total_length);
    if (result == NULL) {
        return NULL;
    }

    size_t current_pos = 0;
    for (size_t i = 0; i < size; i++) {
        if (list[i] != NULL) {
            size_t len = strlen(list[i]);
            if (len > 0 && current_pos + len >= total_length) {
                free(result);
                return NULL;
            }
            if (len > 0) {
                memcpy(result + current_pos, list[i], len);
            }
            current_pos += len;
        }
    }

    if (current_pos < total_length) {
        result[current_pos] = '\0';
    }

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