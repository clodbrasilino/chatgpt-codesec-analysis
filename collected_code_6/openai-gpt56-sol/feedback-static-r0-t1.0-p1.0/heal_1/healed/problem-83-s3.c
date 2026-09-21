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
    unsigned int sum = 0U;
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
        sum = (sum + (unsigned char)character) % (UCHAR_MAX + 1U);
    }

    if (character == EOF && ferror(stdin)) {
        return 1;
    }

    char result_string[2] = {(char)(unsigned char)sum, '\0'};
    unsigned char result = add_characters(result_string);

    if (putchar((int)result) == EOF || putchar('\n') == EOF) {
        return 1;
    }

    return 0;
}