#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *concatenate_list(char **list, int size) {
    if (list == NULL || size <= 0) {
        return NULL;
    }

    size_t total_length = 0;
    for (int i = 0; i < size; i++) {
        if (list[i] == NULL) {
            return NULL;
        }
        size_t len = strnlen(list[i], SIZE_MAX);
        if (len > SIZE_MAX - total_length) {
            return NULL;
        }
        total_length += len;
    }

    char *result = (char *)malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t current_pos = 0;
    for (int i = 0; i < size; i++) {
        size_t len = strnlen(list[i], total_length - current_pos + 1);
        if (current_pos + len > total_length) {
            free(result);
            return NULL;
        }
        if (len > 0) {
            if (current_pos + len > total_length) {
                free(result);
                return NULL;
            }
            memcpy(result + current_pos, list[i], len);
            current_pos += len;
        }
    }
    result[current_pos] = '\0';

    return result;
}

int main(void) {
    char *list[] = {"Hello", " ", "World", "!"};
    int size = sizeof(list) / sizeof(list[0]);

    char *result = concatenate_list(list, size);
    if (result == NULL) {
        fprintf(stderr, "Failed to concatenate list\n");
        return 1;
    }

    printf("%s\n", result);
    free(result);

    return 0;
}