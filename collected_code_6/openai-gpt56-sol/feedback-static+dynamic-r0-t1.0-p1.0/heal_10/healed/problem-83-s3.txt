#include <limits.h>
#include <stdio.h>

static unsigned char add_characters(const unsigned char *data, size_t length)
{
    unsigned int sum = 0U;

    for (size_t i = 0U; i < length; ++i) {
        sum = (sum + data[i]) % (UCHAR_MAX + 1U);
    }

    return (unsigned char)sum;
}

int main(void)
{
    unsigned char buffer[4096];
    unsigned int sum = 0U;
    int character;
    size_t length = 0U;

    while ((character = getchar()) != EOF && character != '\n') {
        buffer[length++] = (unsigned char)character;

        if (length == sizeof buffer) {
            sum = (sum + add_characters(buffer, length)) % (UCHAR_MAX + 1U);
            length = 0U;
        }
    }

    if (ferror(stdin)) {
        return 1;
    }

    if (length > 0U) {
        sum = (sum + add_characters(buffer, length)) % (UCHAR_MAX + 1U);
    }

    if (character == EOF && sum == 0U) {
        return 0;
    }

    if (putchar((int)(unsigned char)sum) == EOF) {
        return 1;
    }

    if (putchar('\n') == EOF) {
        return 1;
    }

    return 0;
}