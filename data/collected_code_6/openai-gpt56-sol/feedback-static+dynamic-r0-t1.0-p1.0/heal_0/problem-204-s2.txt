#include <stdio.h>
#include <stdlib.h>

static size_t count_character(const char *string, int character)
{
    size_t count = 0;

    if (string == NULL) {
        return 0;
    }

    while (*string != '\0') {
        if ((unsigned char)*string == (unsigned char)character) {
            ++count;
        }
        ++string;
    }

    return count;
}

int main(void)
{
    char input[1024];
    char target_input[3];

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read the string.\n", stderr);
        return EXIT_FAILURE;
    }

    size_t length = 0;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (input[length] != '\0') {
        int discarded;
        do {
            discarded = getchar();
        } while (discarded != '\n' && discarded != EOF);
    }

    if (fgets(target_input, sizeof target_input, stdin) == NULL) {
        fputs("Failed to read the character.\n", stderr);
        return EXIT_FAILURE;
    }

    if (target_input[0] == '\n' || target_input[0] == '\0') {
        fputs("No character was provided.\n", stderr);
        return EXIT_FAILURE;
    }

    if (target_input[1] != '\n' && target_input[1] != '\0') {
        int discarded;
        do {
            discarded = getchar();
        } while (discarded != '\n' && discarded != EOF);

        fputs("Provide exactly one character.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%zu\n", count_character(input, (unsigned char)target_input[0]));
    return EXIT_SUCCESS;
}