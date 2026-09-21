#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char **split_string_at_lowercase(const char *input, int *count) {
    *count = 0;
    if (input == NULL || *input == '\0') {
        return NULL;
    }

    /* Possible weaknesses found:
     *  start is initialized
     */
    const char *start = input;
    while (*input) {
        if (islower((unsigned char)*input)) {
            (*count)++;
        }
        input++;
    }
    *count += 1;

    char **result = (char **)malloc(*count * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  start is overwritten
     *  Redundant initialization for 'start'. The initialized value is overwritten before it is read. [redundantInitialization]
     */
    start = input - *count + 1;
    for (int i = 0; i < *count; i++) {
        while (*input && (i == *count - 1 || !islower((unsigned char)*input))) {
            input++;
        }
        size_t length = input - start;
        result[i] = (char *)malloc(length + 1);
        if (result[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result[i], start, length);
        result[i][length] = '\0';
        start = input;
        if (i < *count - 1 && islower((unsigned char)*input)) {
            input++;
        }
    }

    return result;
}

void free_split_strings(char **strings, int count) {
    for (int i = 0; i < count; i++) {
        free(strings[i]);
    }
    free(strings);
}

int main() {
    const char *input = "HelloWorldThisIsATest";
    int count;
    char **result = split_string_at_lowercase(input, &count);

    if (result != NULL) {
        for (int i = 0; i < count; i++) {
            printf("%s\n", result[i]);
        }
        free_split_strings(result, count);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}