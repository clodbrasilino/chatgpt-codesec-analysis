#include <limits.h>
#include <stdio.h>

static unsigned char add_characters(const unsigned char *string)
{
    unsigned int sum = 0U;

    while (*string != '\0') {
        sum = (sum + *string) % (UCHAR_MAX + 1U);
        ++string;
    }

    return (unsigned char)sum;
}

int main(void)
{
    unsigned int sum = 0U;
    int character;

    while ((character = getchar()) != EOF && character != '\n') {
        sum = (sum + (unsigned char)character) % (UCHAR_MAX + 1U);
    }

    if (ferror(stdin)) {
        return 1;
    }

    {
        unsigned char result_string[2];
        unsigned char result;

        result_string[0] = (unsigned char)sum;
        result_string[1] = '\0';
        result = add_characters(result_string);

        if (putchar((int)result) == EOF) {
            return 1;
        }
    }

    if (putchar('\n') == EOF) {
        return 1;
    }

    return 0;
}