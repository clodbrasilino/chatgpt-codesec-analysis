#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concatenate_list(char **list, size_t size) {
    size_t total_length = 0;
    size_t i;

    for (i = 0; i < size; i++) {
        if (list[i] != NULL) {
            size_t remaining = (total_length > 1024 * 1024) ? 0 : (1024 * 1024 - total_length);
            size_t len = strnlen(list[i], remaining);
            if (len == remaining && len != 0) return NULL;
            total_length += len;
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

    size_t current_pos = 0;

    for (i = 0; i < size; i++) {
        if (list[i] != NULL) {
            size_t remaining = total_length - current_pos;
            size_t len = strnlen(list[i], remaining);
            if (len > 0) {
                if (current_pos + len <= total_length) {
                    memcpy(result + current_pos, list[i], len);
                }
            }
            current_pos += len;
        }
    }
    
    result[total_length] = '\0';

    return result;
}

int main(void) {
    char *list[] = {"Hello", ", ", "world", "!"};
    size_t size = sizeof(list) / sizeof(list[0]);

    char *concatenated = concatenate_list(list, size);
    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
        concatenated = NULL;
    }

    return 0;
}