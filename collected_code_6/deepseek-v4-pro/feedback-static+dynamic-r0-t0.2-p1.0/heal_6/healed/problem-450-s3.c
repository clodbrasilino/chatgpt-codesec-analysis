#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extract_strings(char **input, int count, int size, int *out_count) {
    char **result;
    int i;
    int valid_count = 0;

    if (input == NULL || count <= 0 || size <= 0 || out_count == NULL) {
        if (out_count != NULL) {
            *out_count = 0;
        }
        return NULL;
    }

    result = (char **)malloc((size_t)count * sizeof(char *));
    if (result == NULL) {
        *out_count = 0;
        return NULL;
    }

    for (i = 0; i < count; i++) {
        if (input[i] == NULL) {
            continue;
        }
        if ((int)strlen(input[i]) >= size) {
            result[valid_count] = (char *)malloc((size_t)(size + 1) * sizeof(char));
            if (result[valid_count] == NULL) {
                int j;
                for (j = 0; j < valid_count; j++) {
                    free(result[j]);
                }
                free(result);
                *out_count = 0;
                return NULL;
            }
            strncpy(result[valid_count], input[i], (size_t)size);
            result[valid_count][size] = '\0';
            valid_count++;
        }
    }

    if (valid_count == 0) {
        free(result);
        *out_count = 0;
        return NULL;
    }

    char **temp = (char **)realloc(result, (size_t)valid_count * sizeof(char *));
    if (temp == NULL) {
        int j;
        for (j = 0; j < valid_count; j++) {
            free(result[j]);
        }
        free(result);
        *out_count = 0;
        return NULL;
    }
    result = temp;

    *out_count = valid_count;
    return result;
}

int main(void) {
    char *strings[] = {"hello", "world", "C", "programming", "test", NULL};
    char **extracted;
    int count;
    int i;

    extracted = extract_strings(strings, 5, 3, &count);
    if (extracted != NULL) {
        for (i = 0; i < count; i++) {
            printf("%s\n", extracted[i]);
            free(extracted[i]);
        }
        free(extracted);
    }

    extracted = extract_strings(strings, 5, 10, &count);
    if (extracted != NULL) {
        for (i = 0; i < count; i++) {
            printf("%s\n", extracted[i]);
            free(extracted[i]);
        }
        free(extracted);
    }

    extracted = extract_strings(NULL, 5, 3, &count);
    if (extracted != NULL) {
        for (i = 0; i < count; i++) {
            free(extracted[i]);
        }
        free(extracted);
    }

    return 0;
}