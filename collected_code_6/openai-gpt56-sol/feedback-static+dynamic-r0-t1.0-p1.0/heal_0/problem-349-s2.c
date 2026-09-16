#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool is_binary_string(const char *string)
{
    if (string == NULL || *string == '\0') {
        return false;
    }

    for (const unsigned char *p = (const unsigned char *)string; *p != '\0'; ++p) {
        if (*p != '0' && *p != '1') {
            return false;
        }
    }

    return true;
}

int main(void)
{
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fprintf(stderr, "Failed to read input.\n");
        } else {
            fprintf(stderr, "No input provided.\n");
        }
        return 1;
    }

    size_t length = strlen(input);

    if (length > 0U && input[length - 1U] == '\n') {
        input[--length] = '\0';
        if (length > 0U && input[length - 1U] == '\r') {
            input[--length] = '\0';
        }
    } else if (length == sizeof input - 1U && !feof(stdin)) {
        int character;

        do {
            character = getchar();
        } while (character != '\n' && character != EOF);

        fprintf(stderr, "Input is too long.\n");
        return 1;
    }

    puts(is_binary_string(input) ? "Binary string" : "Not a binary string");
    return 0;
}