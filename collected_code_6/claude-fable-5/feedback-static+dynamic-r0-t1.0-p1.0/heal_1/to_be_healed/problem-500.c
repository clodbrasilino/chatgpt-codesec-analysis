#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concatenate_list(const char *const *list, size_t count)
{
    size_t total = 1;
    size_t i;
    char *result;

    if (list == NULL || count == 0) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        size_t len;

        if (list[i] == NULL) {
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        len = strlen(list[i]);
        if (total > SIZE_MAX - len) {
            return NULL;
        }
        total += len;
    }

    result = malloc(total);
    if (result == NULL) {
        return NULL;
    }

    result[0] = '\0';
    for (i = 0; i < count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
         */
        strcat(result, list[i]);
    }

    return result;
}

int main(void)
{
    const char *const words[] = { "Hello", ", ", "world", "!" };
    size_t count = sizeof(words) / sizeof(words[0]);
    char *joined;

    joined = concatenate_list(words, count);
    if (joined == NULL) {
        fprintf(stderr, "Concatenation failed\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", joined) < 0) {
        free(joined);
        return EXIT_FAILURE;
    }

    free(joined);
    return EXIT_SUCCESS;
}