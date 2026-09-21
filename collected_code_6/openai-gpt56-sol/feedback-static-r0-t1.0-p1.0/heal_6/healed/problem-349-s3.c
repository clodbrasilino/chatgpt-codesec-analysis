#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_binary_string(const char *str)
{
    if (str == NULL || *str == '\0') {
        return false;
    }

    while (*str != '\0') {
        if (*str != '0' && *str != '1') {
            return false;
        }
        ++str;
    }

    return true;
}

int main(void)
{
    char input[4096];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    size_t length = 0;

    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (input[length] == '\0' && !feof(stdin)) {
        int ch;

        do {
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }

        if (fputs("Not a binary string\n", stdout) == EOF) {
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }

    if (fputs(is_binary_string(input)
                  ? "Binary string\n"
                  : "Not a binary string\n",
              stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}