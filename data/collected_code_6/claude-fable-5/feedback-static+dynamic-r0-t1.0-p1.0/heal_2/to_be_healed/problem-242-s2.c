#include <stdio.h>
#include <stddef.h>

#define BUFFER_SIZE 256
 /* Possible weaknesses found:
  *  test case 0 failed: expected 18, got <no output>
  *  test case 1 failed: expected 8, got <no output>
  *  test case 2 failed: expected 5, got <no output>
  */

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

void strip_newline(char *str, size_t max_len)
{
    size_t i = 0;

    if (str == NULL)
    {
        return;
    }

    while (i < max_len && str[i] != '\0')
    {
        if (str[i] == '\n')
        {
            str[i] = '\0';
            break;
        }
        i++;
    }
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    size_t length;

    printf("Enter a string: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    strip_newline(buffer, sizeof(buffer));

    length = count_characters(buffer);

    printf("Total characters: %zu\n", length);

    return 0;
}