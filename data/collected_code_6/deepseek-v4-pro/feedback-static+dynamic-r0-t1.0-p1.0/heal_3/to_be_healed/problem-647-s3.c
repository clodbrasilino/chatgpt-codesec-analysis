#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **split_at_uppercase(const char *str, int *count) {
    if (str == NULL || count == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);

    size_t max_parts = len + 1;
    char **result = malloc(max_parts * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    *count = 0;
    size_t start = 0;
    size_t i;

    for (i = 1; i <= len; i++) {
        if (i == len || isupper((unsigned char)str[i])) {
            size_t part_len = i - start;
            char *part = malloc(part_len + 1);
            if (part == NULL) {
                for (int j = 0; j < *count; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            if (part_len > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(part, str + start, part_len);
            }
            part[part_len] = '\0';
            result[*count] = part;
            (*count)++;
            start = i;
        }
    }

    return result;
}

int main(void) {
    const char *test = "helloWorldExample";
    int count = 0;
    char **parts = split_at_uppercase(test, &count);

    if (parts == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        printf("%s\n", parts[i]);
        free(parts[i]);
    }
    free(parts);

    return 0;
}