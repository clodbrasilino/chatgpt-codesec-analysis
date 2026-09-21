#include <limits.h>
#include <stddef.h>
#include <stdio.h>

int first_repeated_character(const char *string, size_t length,
                             unsigned char *result)
{
    unsigned char seen[UCHAR_MAX + 1] = {0};

    if (string == NULL || result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char character = (unsigned char)string[i];

        if (seen[character] != 0) {
            *result = character;
            return 1;
        }

        seen[character] = 1;
    }

    return 0;
}

int main(void)
{
    char input[1024];
    unsigned char repeated_character;

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            return 1;
        }
        return 0;
    }

    size_t length = 0;
    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length == sizeof input) {
        fputs("Input is too long.\n", stderr);
        return 1;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        int character;

        while ((character = getchar()) != '\n' && character != EOF) {
        }

        fputs("Input is too long.\n", stderr);
        return 1;
    }

    int status = first_repeated_character(input, length,
                                          &repeated_character);

    if (status < 0) {
        fputs("Invalid argument.\n", stderr);
        return 1;
    }

    if (status == 1) {
        printf("%c\n", (int)repeated_character);
    } else {
        puts("No repeated character found.");
    }

    return 0;
}