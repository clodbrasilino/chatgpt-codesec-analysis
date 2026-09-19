#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** extract_substrings(char** strings, int size) {
    if (strings == NULL || size < 0) {
        return NULL;
    }

    int count = 0;
    while (strings[count] != NULL) {
        count++;
    }

    char** result = (char**)malloc((count + 1) * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }

    char** valid = (char**)malloc(count * sizeof(char*));
    if (valid == NULL) {
        free(result);
        return NULL;
    }

    int valid_count = 0;

    for (int i = 0; i < count; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        size_t len = strlen(strings[i]);
        if (len <= (size_t)size) {
            valid[valid_count] = (char*)malloc(len + 1);
            if (valid[valid_count] == NULL) {
                for (int j = 0; j < valid_count; j++) {
                    free(valid[j]);
                }
                free(valid);
                free(result);
                return NULL;
            }
            strcpy(valid[valid_count], strings[i]);
            result[valid_count] = valid[valid_count];
            valid_count++;
        }
    }

    result[valid_count] = NULL;
    free(valid);
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

    int extract_size = 8;

    char** extracted = extract_substrings(input_strings, extract_size);
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