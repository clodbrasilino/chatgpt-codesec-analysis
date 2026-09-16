#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int replace_spaces(char *str, char replacement)
{
    size_t i;
    size_t len;

    if (str == NULL) {
        return -1;
    }

    if (replacement == '\0') {
        return -1;
    }

    len = strlen(str);

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
    int result;

    result = replace_spaces(buffer, '_');
    if (result != 0) {
        fprintf(stderr, "Error: failed to replace spaces\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", buffer) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}