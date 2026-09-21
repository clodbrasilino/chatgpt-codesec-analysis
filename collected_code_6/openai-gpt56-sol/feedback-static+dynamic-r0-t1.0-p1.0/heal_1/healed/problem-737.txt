#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool starts_with_vowel(const char *str)
{
    if (str == NULL) {
        return false;
    }

    switch (str[0]) {
    case 'A':
    case 'E':
    case 'I':
    case 'O':
    case 'U':
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
        return true;
    default:
        return false;
    }
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length = getline(&input, &capacity, stdin);

    if (length < 0) {
        free(input);
        return 1;
    }

    if (starts_with_vowel(input)) {
        puts("The string starts with a vowel.");
    } else {
        puts("The string does not start with a vowel.");
    }

    free(input);
    return 0;
}