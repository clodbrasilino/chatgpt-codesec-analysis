#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define BUFFER_SIZE 256

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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
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

    buffer[sizeof(buffer) - 1] = '\0';

    len = strnlen(buffer, sizeof(buffer));
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