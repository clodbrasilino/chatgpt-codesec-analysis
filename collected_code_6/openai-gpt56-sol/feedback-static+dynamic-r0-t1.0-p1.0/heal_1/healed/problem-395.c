#include <limits.h>
#include <stddef.h>
#include <stdio.h>

static int find_first_non_repeated(const unsigned char *data,
                                   size_t length,
                                   unsigned char *result)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
    size_t i;

    if (data == NULL || result == NULL) {
        return 0;
    }

    for (i = 0; i < length; ++i) {
        ++frequencies[data[i]];
    }

    for (i = 0; i < length; ++i) {
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
    int character;

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length >= sizeof input) {
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

    if (find_first_non_repeated(input, length, &result)) {
        if (printf("%c\n", (int)result) < 0) {
            return 1;
        }
    } else {
        if (puts("No non-repeated character found") == EOF) {
            return 1;
        }
    }

    return 0;
}