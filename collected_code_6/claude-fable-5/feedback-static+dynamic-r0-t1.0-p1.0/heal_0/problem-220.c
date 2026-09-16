#include <stdio.h>
#include <stddef.h>

size_t replace_chars(char *str, size_t n)
{
    size_t count = 0;
    size_t i;

    if (str == NULL) {
        return 0;
    }

    for (i = 0; str[i] != '\0' && count < n; i++) {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            str[i] = ':';
            count++;
        }
    }

    return count;
}

int main(void)
{
    char text[] = "Hello, world. This is a test, with punctuation.";
    size_t max_replacements = 5;
    size_t replaced;

    printf("Original: %s\n", text);

    replaced = replace_chars(text, max_replacements);

    printf("Modified: %s\n", text);
    printf("Replacements made: %zu\n", replaced);

    return 0;
}