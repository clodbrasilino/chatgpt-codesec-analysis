#include <stdlib.h>
#include <string.h>

char *concatenate_list(const char *const list[], size_t count) {
    size_t total_length = 0;
    for (size_t i = 0; i < count; i++) {
        if (list[i] != NULL) {
            size_t len = strnlen(list[i], SIZE_MAX);
            total_length += len;
        }
    }

    char *result = (char *)malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    result[0] = '\0';
    for (size_t i = 0; i < count; i++) {
        if (list[i] != NULL) {
            size_t current_len = strnlen(result, total_length);
            size_t src_len = strnlen(list[i], SIZE_MAX);
            size_t remaining = total_length - current_len;
            if (src_len > remaining) {
                free(result);
                return NULL;
            }
            memcpy(result + current_len, list[i], src_len);
            result[current_len + src_len] = '\0';
        }
    }

    return result;
}

int main(void) {
    const char *words[] = {"Hello", " ", "World", "!"};
    size_t count = sizeof(words) / sizeof(words[0]);

    char *result = concatenate_list(words, count);
    if (result != NULL) {
        free(result);
    }

    return 0;
}