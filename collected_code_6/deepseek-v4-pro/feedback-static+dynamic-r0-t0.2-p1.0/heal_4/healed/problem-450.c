#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extract_strings(char **input, int count, int size, int *result_count) {
    if (input == NULL || count <= 0 || size <= 0 || result_count == NULL) {
        if (result_count != NULL) {
            *result_count = 0;
        }
        return NULL;
    }

    int extracted = 0;
    for (int i = 0; i < count; i++) {
        if (input[i] == NULL) {
            continue;
        }
        size_t len = strlen(input[i]);
        if (len >= (size_t)size) {
            extracted++;
        }
    }

    if (extracted == 0) {
        *result_count = 0;
        return NULL;
    }

    char **result = (char **)malloc((size_t)extracted * sizeof(char *));
    if (result == NULL) {
        *result_count = 0;
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < count; i++) {
        if (input[i] == NULL) {
            continue;
        }
        size_t len = strlen(input[i]);
        if (len < (size_t)size) {
            continue;
        }

        result[index] = (char *)malloc(((size_t)size + 1) * sizeof(char));
        if (result[index] == NULL) {
            for (int j = 0; j < index; j++) {
                free(result[j]);
            }
            free(result);
            *result_count = 0;
            return NULL;
        }
        memcpy(result[index], input[i], (size_t)size);
        result[index][size] = '\0';
        index++;
    }

    *result_count = extracted;
    return result;
}

int main(void) {
    char *strings[] = {"practice", "solution", "Python", "exercise"};
    int count = sizeof(strings) / sizeof(strings[0]);
    int result_count = 0;

    char **extracted = extract_strings(strings, count, 7, &result_count);

    if (extracted != NULL) {
        for (int i = 0; i < result_count; i++) {
            printf("%s\n", extracted[i]);
            free(extracted[i]);
        }
        free(extracted);
    } else {
        printf("No strings extracted or error occurred.\n");
    }

    return 0;
}