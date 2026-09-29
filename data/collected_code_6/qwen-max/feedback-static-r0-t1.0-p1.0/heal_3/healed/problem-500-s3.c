#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_list(char **list, int count) {
    size_t total_len = 0;
    for (int i = 0; i < count; i++) {
        total_len += strlen(list[i]) + 1;
    }
    total_len += count - 1;
    char *result = malloc(total_len);
    if (result == NULL) {
        return NULL;
    }
    *result = '\0';
    for (int i = 0; i < count; i++) {
        strncat(result, list[i], total_len - strlen(result) - 1);
        if (i < count - 1) {
            strncat(result, " ", total_len - strlen(result) - 1);
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
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    return 0;
}