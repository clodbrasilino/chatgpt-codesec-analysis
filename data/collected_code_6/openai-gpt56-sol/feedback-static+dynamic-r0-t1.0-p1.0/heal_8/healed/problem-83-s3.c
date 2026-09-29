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
    unsigned char input[1024];
    size_t length = 0U;
    int character;

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length == sizeof input) {
            while ((character = fgetc(stdin)) != '\n' && character != EOF) {
            }

            if (ferror(stdin)) {
                return 1;
            }

            return 1;
        }

        input[length++] = (unsigned char)character;
    }

    if (ferror(stdin)) {
        return 1;
    }

    if (character == EOF && length == 0U) {
        return 0;
    }

    if (putchar((int)add_characters(input, length)) == EOF ||
        putchar('\n') == EOF) {
        return 1;
    }

    return 0;
}