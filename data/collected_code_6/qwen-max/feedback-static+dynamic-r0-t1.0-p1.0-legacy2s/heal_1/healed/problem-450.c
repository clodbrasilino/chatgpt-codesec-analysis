#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extract_strings(const char *source[], int count, size_t size) {
    char **result = (char **)malloc(count * sizeof(char *));
    if (result == NULL) return NULL;
    
    for (int i = 0; i < count; i++) {
        result[i] = (char *)malloc(size + 1);
        if (result[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
        strncpy(result[i], source[i], size);
        result[i][size] = '\0';
    }
    
    return result;
}

void free_strings(char **strings, int count) {
    for (int i = 0; i < count; i++) {
        free(strings[i]);
    }
    free(strings);
}

int main() {
    const char *source[] = {"practice", "solution"};
    int count = 2;
    size_t size = 9;

    char **result = extract_strings(source, count, size);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        printf("%s\n", result[i]);
    }

    free_strings(result, count);

    return 0;
}