#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 4096

void replace_chars(char *str, size_t max_len)
{
    size_t i;
    size_t len;

    if (str == NULL) {
        return;
    }

    len = strnlen(str, max_len);
    for (i = 0; i < len; i++) {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            str[i] = ':';
        }
    }
}

int main(void)
{
    const char source[] = "Hello, world. This is a test.";
    char *buffer;
    size_t len;
    size_t size;

    len = strnlen(source, MAX_STR_LEN);
    if (len >= MAX_STR_LEN) {
        fprintf(stderr, "Source string too long or not terminated\n");
        return EXIT_FAILURE;
    }

    size = len + 1;
    buffer = (char *)malloc(size);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, source, len);
    buffer[len] = '\0';

    replace_chars(buffer, size);

    if (printf("Original: %s\n", source) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }
    if (printf("Modified: %s\n", buffer) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);
    buffer = NULL;

    return EXIT_SUCCESS;
}