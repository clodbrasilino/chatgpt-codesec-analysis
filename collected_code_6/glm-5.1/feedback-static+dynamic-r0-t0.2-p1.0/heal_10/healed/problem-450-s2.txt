#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** extract_substrings(const char** strings, size_t count, size_t n) {
    if (strings == NULL || count == 0 || n == 0) {
        return NULL;
    }

    char** result = (char**)malloc((count + 1) * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }

    size_t actual_count = 0;
    for (size_t i = 0; i < count; i++) {
        if (strings[i] == NULL) {
            for (size_t j = 0; j < actual_count; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        size_t len = strnlen(strings[i], n + 1);

        if (len == n) {
            result[actual_count] = (char*)malloc((n + 1) * sizeof(char));
            if (result[actual_count] == NULL) {
                for (size_t j = 0; j < actual_count; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }

            memcpy(result[actual_count], strings[i], n);
            result[actual_count][n] = '\0';
            actual_count++;
        }
    }

    result[actual_count] = NULL;
    char** temp = (char**)realloc(result, (actual_count + 1) * sizeof(char*));
    if (temp != NULL) {
        result = temp;
    }

    return result;
}

void free_extracted_strings(char** strings) {
    if (strings == NULL) {
        return;
    }

    for (size_t i = 0; strings[i] != NULL; i++) {
        free(strings[i]);
    }
    free(strings);
}

int main(void) {
    const char* input_strings[] = {
        "Python",
        "list",
        "exercises",
        "practice",
        "solution",
        NULL
    };

    size_t count = 0;
    while (input_strings[count] != NULL) {
        count++;
    }

    size_t extract_size = 8;

    char** extracted = extract_substrings(input_strings, count, extract_size);
    if (extracted == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; extracted[i] != NULL; i++) {
        printf("%s\n", extracted[i]);
    }

    free_extracted_strings(extracted);

    return EXIT_SUCCESS;
}