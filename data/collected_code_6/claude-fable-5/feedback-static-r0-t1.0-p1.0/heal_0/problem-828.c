#include <stdio.h>
#include <ctype.h>
#include <string.h>

void count_characters(const char *str, size_t *alphabets, size_t *digits, size_t *specials)
{
    size_t i;

    if (str == NULL || alphabets == NULL || digits == NULL || specials == NULL)
    {
        return;
    }

    *alphabets = 0;
    *digits = 0;
    *specials = 0;

    for (i = 0; str[i] != '\0'; i++)
    {
        unsigned char c = (unsigned char)str[i];

        if (isalpha(c))
        {
            (*alphabets)++;
        }
        else if (isdigit(c))
        {
            (*digits)++;
        }
        else if (!isspace(c))
        {
            (*specials)++;
        }
    }
}

int main(void)
{
    char buffer[256];
    size_t alphabets;
    size_t digits;
    size_t specials;
    size_t len;

    printf("Enter a string: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
    }

    count_characters(buffer, &alphabets, &digits, &specials);

    printf("Alphabets: %zu\n", alphabets);
    printf("Digits: %zu\n", digits);
    printf("Special characters: %zu\n", specials);

    return 0;
}