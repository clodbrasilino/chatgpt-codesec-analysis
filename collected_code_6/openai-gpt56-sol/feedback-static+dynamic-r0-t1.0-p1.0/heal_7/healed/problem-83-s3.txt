#include <limits.h>
#include <stdio.h>

static unsigned char add_characters(const char *string)
{
    unsigned int sum = 0U;

    while (*string != '\0') {
        sum = (sum + (unsigned char)*string) % (UCHAR_MAX + 1U);
        ++string;
    }

    return (unsigned char)sum;
}

int main(void)
{
    char input[1024];
    size_t length = 0U;
    int character;

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length >= sizeof input - 1U) {
            do {
                character = fgetc(stdin);
            } while (character != '\n' && character != EOF);

            return 1;
        }

        input[length++] = (char)character;
    }

    if (ferror(stdin)) {
        return 1;
    }

    if (character == EOF && length == 0U) {
        return 0;
    }

    input[length] = '\0';

    if (putchar((int)add_characters(input)) == EOF ||
        putchar('\n') == EOF) {
        return 1;
    }

    return 0;
}