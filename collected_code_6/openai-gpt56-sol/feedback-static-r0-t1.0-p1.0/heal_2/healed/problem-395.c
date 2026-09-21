#include <limits.h>
#include <stddef.h>
#include <stdio.h>

static int find_first_non_repeated(const unsigned char *data,
                                   size_t length,
                                   unsigned char *result)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};

    if (data == NULL || result == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        ++frequencies[data[i]];
    }

    for (size_t i = 0; i < length; ++i) {
        if (frequencies[data[i]] == 1U) {
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
    int character = EOF;
    int input_too_long = 0;

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length < sizeof input) {
            input[length++] = (unsigned char)character;
        } else {
            input_too_long = 1;
        }
    }

    if (ferror(stdin)) {
        return 1;
    }

    if (input_too_long) {
        return 1;
    }

    if (find_first_non_repeated(input, length, &result)) {
        if (printf("%c\n", (int)result) < 0) {
            return 1;
        }
    } else if (puts("No non-repeated character found") == EOF) {
        return 1;
    }

    return 0;
}