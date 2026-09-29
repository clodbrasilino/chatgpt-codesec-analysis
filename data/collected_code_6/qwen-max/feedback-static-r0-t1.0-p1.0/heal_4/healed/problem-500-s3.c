#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_list(char **list, int count) {
    size_t total_len = 0;
    for (int i = 0; i < count; i++) {
        if (list[i] == NULL) return NULL;
        total_len += strlen(list[i]) + 1;
    }
    total_len += count - 1;
    char *result = malloc(total_len);
    if (result == NULL) {
        return NULL;
    }
    *result = '\0';
    for (int i = 0; i < count; i++) {
        size_t remaining_len = total_len - strlen(result) - 1;
        if (remaining_len <= 0) return NULL;
        strncat(result, list[i], remaining_len);
        if (i < count - 1) {
            strncat(result, " ", remaining_len - strlen(result) - 1);
        }
    }
    return result;
}

int main() {
    char *words[] = {"Hello", "world", "this", "is", "C"};
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