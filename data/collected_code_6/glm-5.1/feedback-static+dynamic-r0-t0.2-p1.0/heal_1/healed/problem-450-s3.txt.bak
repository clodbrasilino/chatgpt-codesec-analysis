#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** extract_substrings(const char** strings, size_t count, size_t size) {
    if (strings == NULL || count == 0 || size == 0) {
        return NULL;
    }

    size_t valid_count = 0;
    for (size_t i = 0; i < count; i++) {
        if (strings[i] != NULL && strlen(strings[i]) >= size) {
            valid_count++;
        }
    }

    if (valid_count == 0) {
        return NULL;
    }

    char** result = (char**)malloc((valid_count + 1) * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < count; i++) {
        if (strings[i] != NULL && strlen(strings[i]) >= size) {
            result[j] = (char*)malloc((size + 1) * sizeof(char));
            if (result[j] == NULL) {
                for (size_t k = 0; k < j; k++) {
                    free(result[k]);
                }
                free(result);
                return NULL;
            }
            strncpy(result[j], strings[i], size);
            result[j][size] = '\0';
            j++;
        }
    }

    result[j] = NULL;
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
        "Hello World",
        "Programming in C",
        "Resource Management",
        "String Extraction"
    };
    size_t count = sizeof(input_strings) / sizeof(input_strings[0]);
    size_t extract_size = 5;

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