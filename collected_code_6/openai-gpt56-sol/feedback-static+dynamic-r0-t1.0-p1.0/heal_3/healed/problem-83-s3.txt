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

    if (fgets(input, sizeof input, stdin) == NULL) {
        return ferror(stdin) ? 1 : 0;
    }

    size_t length = 0U;

    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length < sizeof input && input[length] == '\n') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        int character;

        while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        }

        if (ferror(stdin)) {
            return 1;
        }

        return 1;
    }

    if (putchar((int)add_characters(input)) == EOF ||
        putchar('\n') == EOF) {
        return 1;
    }

    return 0;
}