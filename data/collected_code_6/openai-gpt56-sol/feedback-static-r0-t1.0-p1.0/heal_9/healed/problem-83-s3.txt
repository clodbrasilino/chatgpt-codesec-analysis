#include <limits.h>
#include <stdio.h>

static unsigned char add_characters(const unsigned char *string, size_t length)
{
    unsigned int sum = 0U;
    size_t index;

    for (index = 0U; index < length; ++index) {
        sum = (sum + string[index]) % (UCHAR_MAX + 1U);
    }

    return (unsigned char)sum;
}

int main(void)
{
    unsigned int sum = 0U;
    int character;
    unsigned char result;

    while ((character = getchar()) != EOF && character != '\n') {
        sum = (sum + (unsigned char)character) % (UCHAR_MAX + 1U);
    }

    if (ferror(stdin)) {
        return 1;
    }

    result = add_characters((const unsigned char *)&sum, 0U);
    result = (unsigned char)sum;

    if (putchar((int)result) == EOF) {
        return 1;
    }

    if (putchar('\n') == EOF) {
        return 1;
    }

    return 0;
}