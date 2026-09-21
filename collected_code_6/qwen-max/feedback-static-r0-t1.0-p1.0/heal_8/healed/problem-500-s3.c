#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_list(const char **list, int count) {
    size_t total_len = 0;
    for (int i = 0; i < count; i++) {
        if (list[i] == NULL) return NULL;
        size_t len = strnlen(list[i], SIZE_MAX);
        total_len += len + 1;
    }
    total_len += count - 1;
    char *result = malloc(total_len + 1);
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';
    size_t current_len = 0;
    for (int i = 0; i < count; i++) {
        size_t len = strnlen(list[i], SIZE_MAX);
        if (total_len - current_len - 1 < len) return NULL;
        snprintf(result + current_len, total_len - current_len, "%s ", list[i]);
        current_len += len + 1;
    }
    result[total_len - 1] = '\0';
    return result;
}

int main() {
    const char *words[] = {"Hello", "world", "this", "is", "C"};
    int count = sizeof(words) / sizeof(words[0]);
    char *concatenated = concatenate_list(words, count);
    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
    } else {
        fprintf(stderr, "Memory allocation or string operation failed\n");
        return 1;
    }
    return 0;
}