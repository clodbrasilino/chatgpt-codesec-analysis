#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_char(char *str, char c)
{
    char *src;
    char *dst;

    if (str == NULL) {
        return;
    }

    src = str;
    dst = str;

    while (*src != '\0') {
        if (*src != c) {
            *dst = *src;
            dst++;
        }
        src++;
    }
    *dst = '\0';
}

int main(void)
{
    const char *original = "hello world, hello everyone";
    char target = 'l';
    size_t len;
    char *buffer;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(original);
    buffer = malloc(len + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, original, len + 1);

    printf("Original: %s\n", buffer);
    remove_char(buffer, target);
    printf("After removing '%c': %s\n", target, buffer);

    free(buffer);
    buffer = NULL;

    return EXIT_SUCCESS;
}