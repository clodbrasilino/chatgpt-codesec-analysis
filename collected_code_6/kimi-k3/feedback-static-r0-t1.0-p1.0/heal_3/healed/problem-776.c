#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool is_vowel(char c)
{
    c = (char)tolower((unsigned char)c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

size_t count_chars_with_vowel_neighbors(const char *str, size_t len)
{
    if (str == NULL)
    {
        return 0;
    }

    size_t count = 0;

    for (size_t i = 0; i < len; i++)
    {
        bool has_vowel_neighbor = false;

        if (i > 0 && is_vowel(str[i - 1]))
        {
            has_vowel_neighbor = true;
        }

        if (i < len - 1 && is_vowel(str[i + 1]))
        {
            has_vowel_neighbor = true;
        }

        if (has_vowel_neighbor && !is_vowel(str[i]))
        {
            count++;
        }
    }

    return count;
}

int main(void)
{
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t len;

    printf("Enter a string: ");

    len = getline(&buffer, &buffer_size, stdin);
    if (len == -1)
    {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return 1;
    }

    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
        len--;
    }

    size_t result = count_chars_with_vowel_neighbors(buffer, (size_t)len);
    printf("Count: %zu\n", result);

    free(buffer);
    return 0;
}