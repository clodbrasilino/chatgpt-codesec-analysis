#include <stdio.h>
#include <stdlib.h>

static int has_valid_digit_frequencies(const char *text)
{
    size_t frequencies[10] = {0};

    if (text == NULL || *text == '\0') {
        return 0;
    }

    for (const unsigned char *p = (const unsigned char *)text; *p != '\0'; ++p) {
        unsigned int digit;

        if (*p < (unsigned char)'0' || *p > (unsigned char)'9') {
            return 0;
        }

        digit = (unsigned int)(*p - (unsigned char)'0');

        if (frequencies[digit] >= digit) {
            return 0;
        }

        ++frequencies[digit];
    }

    return 1;
}

static int read_line(char *buffer, size_t capacity)
{
    size_t length;

    if (buffer == NULL || capacity < 2) {
        return 0;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return 0;
    }

    for (length = 0; length < capacity && buffer[length] != '\0'; ++length) {
        if (buffer[length] == '\n') {
            buffer[length] = '\0';
            return 1;
        }
    }

    if (length == 0 || length >= capacity) {
        return 0;
    }

    if (feof(stdin)) {
        return 1;
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];

    if (!read_line(input, sizeof input)) {
        return EXIT_FAILURE;
    }

    if (printf("%s\n",
               has_valid_digit_frequencies(input) ? "true" : "false") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}