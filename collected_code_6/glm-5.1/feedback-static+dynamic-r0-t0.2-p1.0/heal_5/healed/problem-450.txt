#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** extract_substrings(char** strings, int count, int size) {
    if (strings == NULL || count <= 0 || size <= 0) {
        return NULL;
    }

    char** result = (char**)malloc((count + 1) * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }

    int actual_count = 0;
    for (int i = 0; i < count; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        size_t str_len = strlen(strings[i]);
        
        if ((size_t)size > str_len) {
            continue;
        }

        result[actual_count] = (char*)malloc(size + 1);
        if (result[actual_count] == NULL) {
            for (int j = 0; j < actual_count; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
        
        strncpy(result[actual_count], strings[i], size);
        result[actual_count][size] = '\0';
        actual_count++;
    }

    result[actual_count] = NULL;
    
    char** trimmed_result = (char**)realloc(result, (actual_count + 1) * sizeof(char*));
    if (trimmed_result != NULL) {
        return trimmed_result;
    }
    
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
        "exercises",
        "practice",
        "solution",
        NULL
    };

    int count = 0;
    while (input_strings[count] != NULL) {
        count++;
    }

    int extract_size = 6;
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