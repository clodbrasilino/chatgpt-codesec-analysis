#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

int count_uppercase(const char *str)
{
    int count = 0;
    if (str == NULL)
    {
        return 0;
    }
    while (*str != '\0')
    {
        if (isupper((unsigned char)*str))
        {
            count++;
        }
        str++;
    }
    return count;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    int result;
    size_t len;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    len = strnlen(buffer, sizeof(buffer));
    if (len == sizeof(buffer))
    {
        fprintf(stderr, "Input too long.\n");
        return 1;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    result = count_uppercase(buffer);
    printf("Number of uppercase characters: %d\n", result);

    return 0;
}