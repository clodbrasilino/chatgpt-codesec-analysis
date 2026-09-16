#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static bool meets_requirements(const char *text, size_t required_length)
{
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    size_t length = 0U;

    if (text == NULL) {
        return false;
    }

    for (const unsigned char *p = (const unsigned char *)text; *p != '\0'; ++p) {
        ++length;
        has_upper = has_upper || (isupper(*p) != 0);
        has_lower = has_lower || (islower(*p) != 0);
        has_digit = has_digit || (isdigit(*p) != 0);
    }

    return length == required_length && has_upper && has_lower && has_digit;
}

int main(void)
{
    enum { BUFFER_SIZE = 256 };
    char input[BUFFER_SIZE];
    size_t required_length;

    if (scanf("%zu", &required_length) != 1) {
        return 1;
    }

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }

    size_t length = strlen(input);

    if (length > 0U && input[length - 1U] == '\n') {
        input[length - 1U] = '\0';
    } else if (length == sizeof input - 1U) {
        ch = getchar();
        if (ch != '\n' && ch != EOF) {
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            return 1;
        }
    }

    puts(meets_requirements(input, required_length) ? "Valid" : "Invalid");
    return 0;
}