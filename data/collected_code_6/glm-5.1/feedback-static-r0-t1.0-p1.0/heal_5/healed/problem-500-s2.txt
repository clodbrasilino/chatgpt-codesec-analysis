#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concatenate_list(char **list, size_t size) {
    size_t total_length = 0;
    size_t i;
    for (i = 0; i < size; i++) {
        if (list[i] != NULL) {
            size_t len = strnlen(list[i], SIZE_MAX);
            if (total_length > SIZE_MAX - len) {
                return NULL;
            }
            total_length += len;
        }
    }

    if (total_length == SIZE_MAX) {
        return NULL;
    }

    char *result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    result[0] = '\0';
    size_t current_pos = 0;
    for (i = 0; i < size; i++) {
        if (list[i] != NULL) {
            size_t len = strnlen(list[i], SIZE_MAX);
            if (len > 0) {
                if (current_pos > total_length - len) {
                    free(result);
                    return NULL;
                }
                if (total_length + 1 - current_pos < len) {
                    free(result);
                    return NULL;
                }
                memcpy(result + current_pos, list[i], len);
                current_pos += len;
            }
        }
    }
    result[current_pos] = '\0';

    return result;
}

int main(void) {
    char *list[] = {"Hello", ", ", "world", "!"};
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