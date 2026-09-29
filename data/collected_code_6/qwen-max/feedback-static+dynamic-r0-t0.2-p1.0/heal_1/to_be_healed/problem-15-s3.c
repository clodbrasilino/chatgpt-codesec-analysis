#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** split_string_at_lowercase(const char *input, int *count) {
    *count = 0;
    if (input == NULL) return NULL;

    const char *p = input;
    while (*p) {
        if (islower((unsigned char)*p)) (*count)++;
        p++;
    }

    char **result = (char **)malloc((*count + 1) * sizeof(char *));
    if (result == NULL) return NULL;

    *count = 0;
    p = input;
    while (*p) {
        if (islower((unsigned char)*p)) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            result[*count] = (char *)malloc(strlen(p) + 1);
            if (result[*count] == NULL) {
                for (int i = 0; i < *count; i++) free(result[i]);
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
             */
            strcpy(result[*count], p + 1);
            (*count)++;
        }
        p++;
    }
    result[*count] = NULL;
    return result;
}

void free_split_strings(char **strings) {
    if (strings == NULL) return;
    for (int i = 0; strings[i] != NULL; i++) {
        free(strings[i]);
    }
    free(strings);
}

int main() {
    const char *input = "HelloWorldExample";
    int count;
    char **result = split_string_at_lowercase(input, &count);

    if (result != NULL) {
        for (int i = 0; i < count; i++) {
            printf("%s\n", result[i]);
        }
        free_split_strings(result);
    }

    return 0;
}