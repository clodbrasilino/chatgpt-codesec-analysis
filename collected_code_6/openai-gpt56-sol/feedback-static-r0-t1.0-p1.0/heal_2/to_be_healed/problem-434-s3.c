#include <stdbool.h>
#include <stdio.h>

static bool matches(const char *str)
{
    if (str == NULL || *str++ != 'a') {
        return false;
    }

    if (*str != 'b') {
        return false;
    }

    do {
        ++str;
    } while (*str == 'b');

    return *str == '\0';
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return ferror(stdin) ? 1 : 0;
    }

    size_t length = 0;

    while (length < sizeof input &&
           input[length] != '\0' &&
           input[length] != '\n' &&
           input[length] != '\r') {
        ++length;
    }

    if (length == sizeof input) {
        fputs("Invalid input.\n", stderr);
        return 1;
    }

    if (input[length] == '\0' && !feof(stdin)) {
        fputs("Input is too long.\n", stderr);
        return 1;
    }

    input[length] = '\0';

    puts(matches(input) ? "Match" : "No match");
    return 0;
}