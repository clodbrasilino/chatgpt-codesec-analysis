#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 1024

void replace_spaces(char *str, char replacement)
{
    size_t i;
    size_t len;

    if (str == NULL) {
        return;
    }

    len = strnlen(str, MAX_STR_LEN);
    for (i = 0; i < len; i++) {
        if (str[i] == ' ') {
            str[i] = replacement;
        }
    }
}

int main(void)
{
    const char *original = "Hello world this is a test";
    char *buffer;
    size_t size;

    size = strnlen(original, MAX_STR_LEN) + 1;
    buffer = malloc(size);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (snprintf(buffer, size, "%s", original) < 0) {
        fprintf(stderr, "String copy failed\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    printf("Before: %s\n", buffer);
    replace_spaces(buffer, '_');
    printf("After:  %s\n", buffer);

    free(buffer);
    buffer = NULL;

    return EXIT_SUCCESS;
}