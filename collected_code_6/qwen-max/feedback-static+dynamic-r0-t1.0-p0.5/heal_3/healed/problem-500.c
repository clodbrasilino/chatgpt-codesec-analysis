#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_list(const char *list[], size_t length) {
    if (length == 0) return NULL;

    size_t total_length = 1; // Start with 1 to account for the final null terminator
    for (size_t i = 0; i < length; ++i) {
        size_t len = strlen(list[i]);
        if (len == 0 || (len > 0 && list[i][len-1] == '\0')) {
            total_length += len;
        } else {
            return NULL; // Non-null-terminated string detected
        }
    }

    char *result = (char *)malloc(total_length);
    if (result == NULL) return NULL;

    result[0] = '\0';
    for (size_t i = 0, j = 0; i < length; ++i) {
        size_t len = strlen(list[i]);
        if (len > 0) {
            memcpy(result + j, list[i], len);
            j += len;
        }
    }
    result[total_length - 1] = '\0';

    return result;
}

int main() {
    const char *list[] = {"Hello", " ", "World", "!"};
    size_t length = sizeof(list) / sizeof(list[0]);

    char *concatenated = concatenate_list(list, length);
    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
    } else {
        fprintf(stderr, "Memory allocation failed or invalid string detected\n");
    }

    return 0;
}