#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** split_at_uppercase(const char *str, int *count) {
    if (str == NULL || count == NULL) return NULL;
    *count = 0;
    const char *start = str;
    char **result = NULL;
    size_t capacity = 0;

    while (*str != '\0') {
        if (isupper((unsigned char)*str)) {
            size_t length = str - start;
            if (capacity <= *count + 1) {
                capacity += 8;
                char **temp = (char **)realloc(result, capacity * sizeof(char *));
                if (temp == NULL) {
                    for (int i = 0; i < *count; i++) free(result[i]);
                    free(result);
                    return NULL;
                }
                result = temp;
            }
            result[*count] = (char *)malloc((length + 1) * sizeof(char));
            if (result[*count] == NULL) {
                for (int i = 0; i < *count; i++) free(result[i]);
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[*count], start, length);
            result[*count][length] = '\0';
            start = str;
            (*count)++;
        }
        str++;
    }

    if (start != str) {
        size_t length = str - start;
        if (capacity <= *count + 1) {
            capacity += 8;
            char **temp = (char **)realloc(result, capacity * sizeof(char *));
            if (temp == NULL) {
                for (int i = 0; i < *count; i++) free(result[i]);
                free(result);
                return NULL;
            }
            result = temp;
        }
        result[*count] = (char *)malloc((length + 1) * sizeof(char));
        if (result[*count] == NULL) {
            for (int i = 0; i < *count; i++) free(result[i]);
            free(result);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result[*count], start, length);
        result[*count][length] = '\0';
        (*count)++;
    }

    while (capacity > *count + 1) {
        char **temp = (char **)realloc(result, (*count + 1) * sizeof(char *));
        if (temp == NULL) break;
        result = temp;
        capacity = *count + 1;
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