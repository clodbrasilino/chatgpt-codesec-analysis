#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool meets_requirements(const char *string, size_t required_length)
{
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    size_t length = 0U;

    if (string == NULL) {
        return false;
    }

    for (; string[length] != '\0'; ++length) {
        const unsigned char character = (unsigned char)string[length];

        if (isupper(character) != 0) {
            has_upper = true;
        } else if (islower(character) != 0) {
            has_lower = true;
        } else if (isdigit(character) != 0) {
            has_digit = true;
        }
    }

    return length == required_length && has_upper && has_lower && has_digit;
}

int main(void)
{
    char input[256];
    size_t required_length;

    if (printf("Required length: ") < 0) {
        return 1;
    }

    if (scanf("%zu", &required_length) != 1) {
        fprintf(stderr, "Invalid length.\n");
        return 1;
    }

    int character;
    do {
        character = getchar();
        if (character == EOF) {
            fprintf(stderr, "Unexpected end of input.\n");
            return 1;
        }
    } while (character != '\n');

    if (printf("String: ") < 0) {
        return 1;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        fprintf(stderr, "Failed to read the string.\n");
        return 1;
    }

    size_t input_length = strlen(input);

    if (input_length > 0U && input[input_length - 1U] == '\n') {
        input[input_length - 1U] = '\0';
    } else if (!feof(stdin)) {
        while ((character = getchar()) != '\n' && character != EOF) {
        }

        fprintf(stderr, "Input is too long.\n");
        return 1;
    }

    if (meets_requirements(input, required_length)) {
        puts("The string meets all requirements.");
        return 0;
    }

    puts("The string does not meet all requirements.");
    return 1;
}