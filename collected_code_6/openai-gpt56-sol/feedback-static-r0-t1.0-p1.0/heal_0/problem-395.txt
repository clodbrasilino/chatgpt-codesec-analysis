#include <limits.h>
#include <stddef.h>
#include <stdio.h>

static int find_first_non_repeated(const char *str, unsigned char *result)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
    const unsigned char *current;

    if (str == NULL || result == NULL) {
        return 0;
    }

    current = (const unsigned char *)str;

    while (*current != '\0') {
        ++frequencies[*current];
        ++current;
    }

    current = (const unsigned char *)str;

    while (*current != '\0') {
        if (frequencies[*current] == 1U) {
            *result = *current;
            return 1;
        }
        ++current;
    }

    return 0;
}

int main(void)
{
    char input[1024];
    unsigned char result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            return 1;
        }
        return 0;
    }

    {
        size_t length = 0;

        while (input[length] != '\0' && input[length] != '\n') {
            ++length;
        }

        if (input[length] == '\n') {
            input[length] = '\0';
        } else if (input[length] == '\0' && !feof(stdin)) {
            int character;

            do {
                character = getchar();
            } while (character != '\n' && character != EOF);

            if (ferror(stdin)) {
                return 1;
            }

            return 1;
        }
    }

    if (find_first_non_repeated(input, &result)) {
        if (printf("%c\n", result) < 0) {
            return 1;
        }
    } else {
        if (printf("No non-repeated character found\n") < 0) {
            return 1;
        }
    }

    return 0;
}