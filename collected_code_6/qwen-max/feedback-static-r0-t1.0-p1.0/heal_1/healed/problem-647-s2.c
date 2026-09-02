#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** split_at_uppercase(const char *str, int *count) {
    if (str == NULL || count == NULL) return NULL;
    int capacity = 10;
    *count = 0;
    char **result = (char **)malloc(capacity * sizeof(char *));
    if (result == NULL) return NULL;

    const char *start = str;
    while (*str != '\0') {
        if (isupper((unsigned char)*str)) {
            if (*count >= capacity - 1) {
                capacity *= 2;
                char **tmp = (char **)realloc(result, capacity * sizeof(char *));
                if (tmp == NULL) {
                    for (int i = 0; i < *count; i++) free(result[i]);
                    free(result);
                    return NULL;
                }
                result = tmp;
            }
            size_t length = str - start;
            result[*count] = (char *)malloc(length * sizeof(char));
            if (result[*count] == NULL) {
                for (int i = 0; i < *count; i++) free(result[i]);
                free(result);
                return NULL;
            }
            memcpy(result[*count], start, length);
            result[*count][length] = '\0';
            start = str;
            (*count)++;
        }
        str++;
    }

    if (start != str) {
        if (*count >= capacity - 1) {
            capacity += 1;
            char **tmp = (char **)realloc(result, capacity * sizeof(char *));
            if (tmp == NULL) {
                for (int i = 0; i < *count; i++) free(result[i]);
                free(result);
                return NULL;
            }
            result = tmp;
        }
        size_t length = str - start;
        result[*count] = (char *)malloc(length * sizeof(char));
        if (result[*count] == NULL) {
            for (int i = 0; i < *count; i++) free(result[i]);
            free(result);
            return NULL;
        }
        memcpy(result[*count], start, length);
        result[*count][length] = '\0';
        (*count)++;
    }

    result[*count] = NULL;
    return result;
}

void free_split_result(char **split_result, int count) {
    for (int i = 0; i < count; i++) free(split_result[i]);
    free(split_result);
}

int main() {
    const char *input = "ExampleOfAStringWithUpperCases";
    int count = 0;
    char **split_result = split_at_uppercase(input, &count);

    if (split_result) {
        for (int i = 0; i < count; i++) {
            printf("%s\n", split_result[i]);
        }
        free_split_result(split_result, count);
    } else {
        fprintf(stderr, "Failed to split string.\n");
    }

    return 0;
}