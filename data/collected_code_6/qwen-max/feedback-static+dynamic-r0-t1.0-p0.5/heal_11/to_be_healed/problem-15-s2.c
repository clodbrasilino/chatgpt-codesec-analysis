#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char **split_string_at_lowercase(const char *input, int *count) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(input);
    if (length == 0) return NULL;

    int capacity = 10;
    char **result = (char **)malloc(capacity * sizeof(char *));
    if (!result) return NULL;

    *count = 0;
    int start = 0;
    for (size_t i = 0; i <= length; ++i) {
        if (i == length || islower((unsigned char)input[i])) {
            if (i > start) {
                if (*count >= capacity - 1) {
                    capacity *= 2;
                    char **new_result = (char **)realloc(result, capacity * sizeof(char *));
                    if (!new_result) {
                        while (*count > 0) free(result[--*count]);
                        free(result);
                        return NULL;
                    }
                    result = new_result;
                }
                size_t len = i - start;
                result[*count] = (char *)malloc((len + 1) * sizeof(char));
                if (!result[*count]) {
                    while (*count > 0) free(result[--*count]);
                    free(result);
                    return NULL;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result[*count], &input[start], len);
                result[*count][len] = '\0';
                (*count)++;
            }
            start = i + 1;
        }
    }
    result[*count] = NULL;
    return result;
}

void free_split_strings(char **strings) {
    if (strings) {
        int i = 0;
        while (strings[i] != NULL) {
            free(strings[i]);
            i++;
        }
        free(strings);
    }
}

int main() {
    const char *input = "HelloWorldThisIsATest";
    int count;
    char **result = split_string_at_lowercase(input, &count);

    if (result) {
        for (int i = 0; i < count; ++i) {
            printf("%s\n", result[i]);
        }
        free_split_strings(result);
    }

    return 0;
}