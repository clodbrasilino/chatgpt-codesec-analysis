#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_INPUT_LENGTH 256

bool is_valid_password(const char *str, size_t required_length);
static void discard_remaining_input(void);

bool is_valid_password(const char *str, size_t required_length)
{
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    size_t length = 0;
    size_t i;

    if (str == NULL) {
        return false;
    }

    if (required_length == 0 || required_length >= MAX_INPUT_LENGTH) {
        return false;
    }

    length = strnlen(str, MAX_INPUT_LENGTH);

    if (length != required_length) {
        return false;
    }

    for (i = 0; i < length; i++) {
        unsigned char c = (unsigned char)str[i];

        if (isupper(c)) {
            has_upper = true;
        } else if (islower(c)) {
            has_lower = true;
        } else if (isdigit(c)) {
            has_digit = true;
        }
    }

    return (has_upper && has_lower && has_digit);
}

static void discard_remaining_input(void)
{
    int ch;
    size_t discarded = 0;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        discarded++;
        if (discarded >= MAX_INPUT_LENGTH) {
            discarded = 0;
        }
    }
}

int main(void)
{
    char buffer[MAX_INPUT_LENGTH];
    size_t required_length = 8;
    size_t input_length;

    memset(buffer, 0, sizeof(buffer));

    printf("Enter a string to validate (required length %zu): ", required_length);

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    input_length = strnlen(buffer, sizeof(buffer));

    if (input_length > 0 && buffer[input_length - 1] == '\n') {
        buffer[input_length - 1] = '\0';
    } else {
        discard_remaining_input();
    }

    if (is_valid_password(buffer, required_length)) {
        printf("The string is valid.\n");
    } else {
        printf("The string is invalid.\n");
    }

    memset(buffer, 0, sizeof(buffer));

    return EXIT_SUCCESS;
}