#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

static bool has_odd_length(size_t length)
{
    return (length & (size_t)1) != 0;
}

int main(void)
{
    bool odd = false;
    bool has_input = false;
    int character;

    while ((character = getchar()) != EOF && character != '\n') {
        odd = !odd;
        has_input = true;
    }

    if (ferror(stdin) || (character == EOF && !has_input)) {
        return 1;
    }

    return puts(odd ? "Odd" : "Even") == EOF ? 1 : 0;
}