#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *concatenate_list(const char *const list[], size_t count) {
    size_t total_length = 0;
    for (size_t i = 0; i < count; i++) {
        if (list[i] != NULL) {
            size_t len = strnlen(list[i], SIZE_MAX);
            if (len > SIZE_MAX - total_length) {
                return NULL;
            }
            total_length += len;
        }
    }

    if (total_length >= SIZE_MAX) {
        return NULL;
    }

    char *result = (char *)malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    result[0] = '\0';
    size_t offset = 0;
    for (size_t i = 0; i < count; i++) {
        if (list[i] != NULL) {
            size_t len = strnlen(list[i], SIZE_MAX);
            if (offset + len > total_length) {
                free(result);
                return NULL;
            }
            memcpy(result + offset, list[i], len);
            offset += len;
        }
    }
    result[offset] = '\0';

    return result;
}

int main(void) {
    const char *words[] = {"Hello", " ", "World", "!", NULL};
    size_t count = sizeof(words) / sizeof(words[0]) - 1;

    char *result = concatenate_list(words, count);
    if (result != NULL) {
        free(result);
    }

    return 0;
}