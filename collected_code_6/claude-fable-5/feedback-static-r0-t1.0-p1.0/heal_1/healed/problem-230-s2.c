#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int replace_spaces(char *str, size_t max_len, char replacement)
{
    size_t i;
    size_t len;

    if (str == NULL) {
        return -1;
    }

    if (replacement == '\0') {
        return -1;
    }

    len = strnlen(str, max_len);

    if (len == max_len) {
        return -1;
    }

    for (i = 0; i < len; i++) {
        if (str[i] == ' ') {
            str[i] = replacement;
        }
    }

    return 0;
}

int main(void)
{
    char buffer[] = "Hello world this is a test";
    char replacement = '_';
    int result;

    printf("Original string: %s\n", buffer);

    result = replace_spaces(buffer, sizeof(buffer), replacement);
    if (result != 0) {
        fprintf(stderr, "Error: failed to replace spaces\n");
        return EXIT_FAILURE;
    }

    printf("Modified string: %s\n", buffer);

    return EXIT_SUCCESS;
}