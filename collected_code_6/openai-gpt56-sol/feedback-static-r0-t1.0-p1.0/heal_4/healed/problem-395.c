#include <limits.h>
#include <stddef.h>
#include <stdio.h>

static int find_first_non_repeated(const unsigned char *data,
                                   size_t length,
                                   unsigned char *result)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};

    if (result == NULL || (data == NULL && length != 0)) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        ++frequencies[data[i]];
    }

    for (size_t i = 0; i < length; ++i) {
        if (frequencies[data[i]] == 1) {
            *result = data[i];
            return 1;
        }
    }

    return 0;
}

int main(void)
{
    unsigned char input[1024];
    unsigned char result;
    size_t length = 0;
    int character;

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length >= sizeof input) {
            while ((character = fgetc(stdin)) != EOF && character != '\n') {
            }

            if (ferror(stdin)) {
                fputs("Input error\n", stderr);
            } else {
                fputs("Input too long\n", stderr);
            }

            return 1;
        }

        input[length++] = (unsigned char)character;
    }

    if (ferror(stdin)) {
        fputs("Input error\n", stderr);
        return 1;
    }

    if (find_first_non_repeated(input, length, &result)) {
        if (putchar((int)result) == EOF || putchar('\n') == EOF) {
            return 1;
        }
    } else if (puts("No non-repeated character found") == EOF) {
        return 1;
    }

    return 0;
}