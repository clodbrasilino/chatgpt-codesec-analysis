#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **split_at_uppercase(const char *input, int *count) {
    int size = 10;
    int index = 0;
    char **result = (char **)malloc(size * sizeof(char *));
    if (!result) return NULL;

    const char *start = input;
    while (*input) {
        if (isupper((unsigned char)*input)) {
            if (index >= size - 1) {
                size *= 2;
                char **new_result = (char **)realloc(result, size * sizeof(char *));
                if (!new_result) {
                    for (int i = 0; i < index; ++i) free(result[i]);
                    free(result);
                    return NULL;
                }
                result = new_result;
            }
            size_t len = input - start;
            result[index] = (char *)malloc(len + 1);
            if (!result[index]) {
                for (int i = 0; i < index; ++i) free(result[i]);
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(result[index], start, len);
            result[index][len] = '\0';
            ++index;
            start = input;
        }
        ++input;
    }

    if (index >= size - 1) {
        size++;
        char **new_result = (char **)realloc(result, size * sizeof(char *));
        if (!new_result) {
            for (int i = 0; i < index; ++i) free(result[i]);
            free(result);
            return NULL;
        }
        result = new_result;
    }
    size_t len = input - start;
    result[index] = (char *)malloc(len + 1);
    if (!result[index]) {
        for (int i = 0; i < index; ++i) free(result[i]);
        free(result);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(result[index], start, len);
    result[index][len] = '\0';
    ++index;

    *count = index;
    return result;
}

void free_split_result(char **result, int count) {
    for (int i = 0; i < count; ++i) {
        free(result[i]);
    }
    free(result);
}

int main() {
    const char *input = "HelloWorldThisIsAString";
    int count;
    char **result = split_at_uppercase(input, &count);

    if (result) {
        for (int i = 0; i < count; ++i) {
            printf("%s\n", result[i]);
        }
        free_split_result(result, count);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    return 0;
}