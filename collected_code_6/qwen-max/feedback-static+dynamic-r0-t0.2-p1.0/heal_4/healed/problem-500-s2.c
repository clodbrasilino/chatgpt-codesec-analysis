#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_list(const char *list[], int size) {
    if (size <= 0) return NULL;

    int total_length = 0;
    for (int i = 0; i < size; ++i) {
        size_t len = strlen(list[i]);
        if (len == 0 || list[i][len-1] != '\0') return NULL;
        total_length += len;
    }

    char *result = (char *)malloc(total_length + 1);
    if (result == NULL) return NULL;

    result[0] = '\0';
    int current_len = 0;
    for (int i = 0; i < size; ++i) {
        size_t len = strlen(list[i]);
        if (len == 0 || list[i][len-1] != '\0') {
            free(result);
            return NULL;
        }
        strncat(result + current_len, list[i], len + 1);
        current_len += len;
    }

    return result;
}

int main() {
    const char *list[] = {"Hello", " ", "World", "!"};
    int size = sizeof(list) / sizeof(list[0]);

    char *concatenated = concatenate_list(list, size);
    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    return 0;
}