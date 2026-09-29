#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

bool ends_with_number(const char *str)
{
    if (str == NULL) {
        return false;
    }

    size_t length = strlen(str);

    if (length == 0) {
        return false;
    }

    return isdigit((unsigned char)str[length - 1]) != 0;
}

int main(void)
{
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fprintf(stderr, "Failed to read input.\n");
            return 1;
        }
        return 0;
    }

    size_t length = strlen(input);

    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';
    } else if (length == sizeof input - 1) {
        int ch;

        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        if (ferror(stdin)) {
            fprintf(stderr, "Failed to read input.\n");
            return 1;
        }
    }

    printf("%s\n", ends_with_number(input) ? "true" : "false");
    return 0;
}