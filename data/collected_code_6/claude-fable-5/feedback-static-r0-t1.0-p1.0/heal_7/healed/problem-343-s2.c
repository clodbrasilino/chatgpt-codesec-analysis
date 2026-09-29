#include <stdio.h>
#include <ctype.h>
#include <stddef.h>
#include <string.h>

#define INPUT_SIZE 256

void count_digits_letters(const char *str, size_t maxlen, size_t *digits, size_t *letters)
{
    size_t i;

    if (str == NULL || digits == NULL || letters == NULL) {
        return;
    }

    *digits = 0;
    *letters = 0;

    for (i = 0; i < maxlen && str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        if (isdigit(c)) {
            (*digits)++;
        } else if (isalpha(c)) {
            (*letters)++;
        }
    }
}

static void flush_stdin(void)
{
    int ch;
    size_t guard = 0;
    const size_t guard_limit = 1000000;

    do {
        ch = getchar();
        guard++;
    } while (ch != '\n' && ch != EOF && guard < guard_limit);
}

int main(void)
{
    char input[INPUT_SIZE];
    size_t digits = 0;
    size_t letters = 0;
    size_t len;

    printf("Enter a string: ");
    if (fflush(stdout) != 0) {
        fprintf(stderr, "Error flushing output\n");
        return 1;
    }

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    input[sizeof(input) - 1] = '\0';

    len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else if (len == sizeof(input) - 1) {
        flush_stdin();
    }

    count_digits_letters(input, sizeof(input), &digits, &letters);

    printf("Digits: %zu\n", digits);
    printf("Letters: %zu\n", letters);

    return 0;
}