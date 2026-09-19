#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extract_strings(char **input, int count, int size, int *output_count) {
    if (input == NULL || count <= 0 || size <= 0 || output_count == NULL) {
        if (output_count != NULL) {
            *output_count = 0;
        }
        return NULL;
    }

    char **result = (char **)malloc((size_t)count * sizeof(char *));
    if (result == NULL) {
        *output_count = 0;
        return NULL;
    }

    int extracted = 0;
    for (int i = 0; i < count; i++) {
        if (input[i] == NULL) {
            continue;
        }
        size_t len = strlen(input[i]);
        if (len < (size_t)size) {
            continue;
        }
        result[extracted] = (char *)malloc(((size_t)size + 1) * sizeof(char));
        if (result[extracted] == NULL) {
            for (int j = 0; j < extracted; j++) {
                free(result[j]);
            }
            free(result);
            *output_count = 0;
            return NULL;
        }
        memcpy(result[extracted], input[i], (size_t)size);
        result[extracted][size] = '\0';
        extracted++;
    }

    if (extracted == 0) {
        free(result);
        *output_count = 0;
        return NULL;
    }

    char **final_result = (char **)realloc(result, (size_t)extracted * sizeof(char *));
    if (final_result == NULL) {
        for (int j = 0; j < extracted; j++) {
            free(result[j]);
        }
        free(result);
        *output_count = 0;
        return NULL;
    }

    *output_count = extracted;
    return final_result;
}

int main(void) {
    char *strings[] = {"hello", "world", "C", "programming", "language", NULL, "test"};
    int count = sizeof(strings) / sizeof(strings[0]);
    int output_count = 0;
    int extract_size = 3;

    char **extracted = extract_strings(strings, count, extract_size, &output_count);

    if (extracted != NULL) {
        for (int i = 0; i < output_count; i++) {
            printf("%s\n", extracted[i]);
            free(extracted[i]);
        }
        free(extracted);
    } else {
        printf("No strings extracted or error occurred\n");
    }

    return 0;
}