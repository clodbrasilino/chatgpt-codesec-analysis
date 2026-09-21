#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool is_vowel(char c)
{
    c = (char)tolower((unsigned char)c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

size_t count_chars_with_vowel_neighbors(const char *str)
{
    if (str == NULL)
    {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];

    printf("Enter a string: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
    }

    size_t result = count_chars_with_vowel_neighbors(buffer);
    printf("Count: %zu\n", result);

    return 0;
}