#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char **split_string(const char *input, int *count) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(input);
    char **result = (char **)malloc((length + 2) * sizeof(char *));
    if (result == NULL) return NULL;
    *count = 0;

    const char *start = input;
    for (size_t i = 0; i <= length; ++i) {
        if (i == length || !islower((unsigned char)input[i])) {
            if (start < &input[i]) {
                size_t segment_length = i - (start - input);
                result[*count] = (char *)malloc((segment_length + 1) * sizeof(char));
                if (result[*count] == NULL) {
                    for (int j = 0; j < *count; ++j) free(result[j]);
                    free(result);
                    return NULL;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result[*count], start, segment_length);
                result[*count][segment_length] = '\0';
                (*count)++;
            }
            if (i < length) start = &input[i];
        }
    }

    result[*count] = NULL;
    return result;
}

void free_split_strings(char **strings, int count) {
    for (int i = 0; i < count; ++i) {
        free(strings[i]);
    }
    free(strings);
}

int main() {
    const char *input = "aBCdEfGHiJKL";
    int count;
    char **result = split_string(input, &count);

    if (result != NULL) {
        for (int i = 0; result[i] != NULL; ++i) {
            printf("%s\n", result[i]);
        }
        free_split_strings(result, count);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}