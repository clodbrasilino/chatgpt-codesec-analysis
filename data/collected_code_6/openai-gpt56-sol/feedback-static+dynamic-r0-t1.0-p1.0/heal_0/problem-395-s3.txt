#include <limits.h>
#include <stddef.h>
#include <stdio.h>

int first_non_repeated_character(const char *str, unsigned char *result)
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
        if (frequencies[*current] == 1) {
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
            fprintf(stderr, "Failed to read input.\n");
            return 1;
        }
        fprintf(stderr, "No input provided.\n");
        return 1;
    }

    size_t length = 0;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (input[length] != '\0') {
        fprintf(stderr, "Input is too long.\n");
        return 1;
    }

    if (first_non_repeated_character(input, &result)) {
        printf("%c\n", result);
    } else {
        printf("No non-repeated character found.\n");
    }

    return 0;
}