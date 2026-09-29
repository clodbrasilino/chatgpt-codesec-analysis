#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 256

int count_vowels(const char *str)
{
    int count = 0;

    if (str == NULL)
    {
        return 0;
    }

    while (*str != '\0')
    {
        int c = tolower((unsigned char)*str);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
        {
            count++;
        }
        str++;
    }

    return count;
}

bool read_input(char *buffer, size_t size)
{
    if (buffer == NULL || size == 0)
    {
        return false;
    }

    if (fgets(buffer, (int)size, stdin) == NULL)
    {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
    }
    else
    {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
    }

    return true;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    int result;

    printf("Enter a string: ");

    if (!read_input(buffer, sizeof(buffer)))
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    result = count_vowels(buffer);
    printf("Number of vowels: %d\n", result);

    return 0;
}