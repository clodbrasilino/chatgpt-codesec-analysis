#include <stdio.h>
#include <stddef.h>

size_t count_characters(const char *str)
{
    size_t count = 0;

    if (str == NULL)
    {
        return 0;
    }

    while (str[count] != '\0')
    {
        count++;
    }

    return count;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    size_t length;
    size_t i;

    printf("Enter a string: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    length = count_characters(buffer);

    for (i = 0; i < length; i++)
    {
        if (buffer[i] == '\n')
        {
            buffer[i] = '\0';
            break;
        }
    }

    length = count_characters(buffer);

    printf("Total characters: %zu\n", length);

    return 0;
}