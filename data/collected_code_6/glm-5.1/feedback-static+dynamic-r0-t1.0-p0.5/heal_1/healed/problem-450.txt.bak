#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** extract_substrings(char** strings, int count, int size) {
    if (strings == NULL || count <= 0 || size < 0) {
        return NULL;
    }

    char** result = (char**)malloc((count + 1) * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        if (strings[i] == NULL) {
            result[i] = NULL;
            continue;
        }

        size_t len = strlen(strings[i]);
        if ((size_t)size > len) {
            result[i] = NULL;
            continue;
        }

        size_t extract_len = (size_t)size;

        result[i] = (char*)malloc(extract_len + 1);
        if (result[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        strncpy(result[i], strings[i], extract_len);
        result[i][extract_len] = '\0';
    }

    result[count] = NULL;
    return result;
}

void free_extracted_strings(char** strings) {
    if (strings == NULL) {
        return;
    }

    for (int i = 0; strings[i] != NULL; i++) {
        free(strings[i]);
    }
    free(strings);
}

int main() {
    char* input_strings[] = {
        "Python",
        "list",
        "exercise",
        "practice",
        "solution",
        NULL
    };

    int count = 0;
    while (input_strings[count] != NULL) {
        count++;
    }

    int extract_size = 8;

    char** extracted = extract_substrings(input_strings, count, extract_size);
    if (extracted == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; extracted[i] != NULL; i++) {
        printf("%s\n", extracted[i]);
    }

    free_extracted_strings(extracted);

    return 0;
}