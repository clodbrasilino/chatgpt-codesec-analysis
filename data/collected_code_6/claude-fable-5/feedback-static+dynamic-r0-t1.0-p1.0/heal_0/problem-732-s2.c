#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replace_chars(char *str)
{
    size_t i;
    size_t len;

    if (str == NULL) {
        return;
    }

    len = strlen(str);
    for (i = 0; i < len; i++) {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            str[i] = ':';
        }
    }
}

int main(void)
{
    const char *source = "Hello, world. This is a test.";
    char *buffer;
    size_t size;

    size = strlen(source) + 1;
    buffer = (char *)malloc(size);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    memcpy(buffer, source, size);

    replace_chars(buffer);

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