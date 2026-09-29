#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **split_string_at_lowercase(const char *input, int *count) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(input);
    char **result = (char **)malloc((length + 2) * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }
    *count = 0;

    const char *start = input;
    for (size_t i = 0; i <= length; ++i) {
        if (i == length || islower((unsigned char)input[i])) {
            size_t len = i - (start - input);
            result[*count] = (char *)malloc((len + 1) * sizeof(char));
            if (result[*count] == NULL) {
                for (int j = 0; j < *count; ++j) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(result[*count], start, len);
            result[*count][len] = '\0';
            (*count)++;
            start = input + i + 1;
        }
    }

    result[*count] = NULL;
    return result;
}

void free_split_strings(char **strings) {
    if (strings != NULL) {
        for (int i = 0; strings[i] != NULL; ++i) {
            free(strings[i]);
        }
        free(strings);
    }
}

int main() {
    const char *input = "AbCdEfGhIjK";
    int count;
    char **result = split_string_at_lowercase(input, &count);

    if (result != NULL) {
        for (int i = 0; i < count; ++i) {
            printf("%s\n", result[i]);
        }
        free_split_strings(result);
    } else {
        fprintf(stderr, "Memory allocation failed.\n");
    }

    return 0;
}