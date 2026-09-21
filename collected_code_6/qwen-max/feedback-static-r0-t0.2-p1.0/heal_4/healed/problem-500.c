#include <stdio.h>
#include <stdlib.h>

char* concatenate_list(const char *list[], size_t length) {
    if (length == 0) return NULL;

    size_t total_length = 0;
    for (size_t i = 0; i < length; ++i) {
        while (list[i][total_length]) {
            total_length++;
        }
    }

    char *result = (char *)malloc(total_length + 1);
    if (result == NULL) return NULL;

    result[0] = '\0';
    char *current_pos = result;
    for (size_t i = 0; i < length; ++i) {
        size_t current_len = 0;
        while (list[i][current_len]) {
            current_pos[current_len] = list[i][current_len];
            current_len++;
        }
        current_pos += current_len;
    }
    *current_pos = '\0';

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
        fprintf(stderr, "Memory allocation failed\n");
    }

    return 0;
}