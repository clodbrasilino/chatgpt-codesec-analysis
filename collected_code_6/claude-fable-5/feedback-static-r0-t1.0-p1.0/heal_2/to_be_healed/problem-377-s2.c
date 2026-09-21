#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 1024

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
    size_t buffer_size;
    char *buffer;

    len = strnlen(original, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        fprintf(stderr, "Input string too long or not terminated\n");
        return EXIT_FAILURE;
    }

    buffer_size = len + 1;
    buffer = malloc(buffer_size);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, original, len);
    buffer[len] = '\0';

    printf("Original: %s\n", buffer);
    remove_char(buffer, target);
    printf("After removing '%c': %s\n", target, buffer);

    free(buffer);
    buffer = NULL;

    return EXIT_SUCCESS;
}