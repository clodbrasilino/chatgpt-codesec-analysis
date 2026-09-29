#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t replace_chars(char *str, char old_char, char new_char);

size_t replace_chars(char *str, char old_char, char new_char)
{
    size_t count = 0;
    size_t i;

    if (str == NULL) {
        return 0;
    }

    if (old_char == '\0' || new_char == '\0') {
        return 0;
    }

    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == old_char) {
            str[i] = new_char;
            count++;
        }
    }

    return count;
}

int main(void)
{
    const char *source = "hello world, hello everyone";
    size_t len;
    char *buffer;
    size_t replaced;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(source);
    buffer = malloc(len + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, source, len + 1);

    printf("Original: %s\n", buffer);

    replaced = replace_chars(buffer, 'l', 'L');

    printf("Modified: %s\n", buffer);
    printf("Replacements made: %zu\n", replaced);

    free(buffer);
    buffer = NULL;

    return EXIT_SUCCESS;
}