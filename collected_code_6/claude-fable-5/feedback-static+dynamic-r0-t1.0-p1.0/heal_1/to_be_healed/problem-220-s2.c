#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t replace_chars(char *str, size_t n)
{
    size_t count = 0;
    size_t i;

    if (str == NULL) {
        return 0;
    }

    for (i = 0; str[i] != '\0' && count < n; i++) {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            str[i] = ':';
            count++;
        }
    }

    return count;
}

int main(void)
{
    const char source[] = "Hello world, this is a test. Replace them all.";
    char *buffer;
    size_t len;
    size_t replaced;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(source);
    buffer = malloc(len + 1U);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, source, len + 1U);

    replaced = replace_chars(buffer, 5U);

    if (printf("Original: %s\n", source) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }
    if (printf("Modified: %s\n", buffer) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }
    if (printf("Replacements made: %zu\n", replaced) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);
    buffer = NULL;

    return EXIT_SUCCESS;
}