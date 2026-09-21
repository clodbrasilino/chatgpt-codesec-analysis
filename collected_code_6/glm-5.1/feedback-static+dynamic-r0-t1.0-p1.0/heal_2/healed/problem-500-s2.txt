#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concatenate_list(char **list, size_t size) {
    size_t total_length = 0;
    size_t i;
    for (i = 0; i < size; i++) {
        if (list[i] != NULL) {
            total_length += strlen(list[i]);
        }
    }

    if (size == 0 || total_length == 0) {
        char *empty_str = malloc(1);
        if (empty_str == NULL) {
            return NULL;
        }
        empty_str[0] = '\0';
        return empty_str;
    }

    char *result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    result[0] = '\0';
    size_t current_length = 0;
    for (i = 0; i < size; i++) {
        if (list[i] != NULL) {
            size_t item_length = strlen(list[i]);
            if (current_length + item_length <= total_length) {
                memcpy(result + current_length, list[i], item_length);
                current_length += item_length;
            }
        }
    }
    result[current_length] = '\0';

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