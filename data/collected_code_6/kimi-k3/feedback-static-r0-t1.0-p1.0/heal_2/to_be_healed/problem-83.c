#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int find_summed_character(const char *str, size_t max_len, char *result)
{
    unsigned long long sum;
    size_t i;
    size_t len;

    if (str == NULL || result == NULL || max_len == 0)
    {
        return -1;
    }

    len = strnlen(str, max_len);
    if (len == 0 || len == max_len)
    {
        return -1;
    }

    sum = 0ULL;
    for (i = 0; i < len; i++)
    {
        sum += (unsigned char)str[i];
        if (sum > (unsigned long long)UCHAR_MAX)
        {
            sum %= ((unsigned long long)UCHAR_MAX + 1ULL);
        }
    }

    *result = (char)(sum % ((unsigned long long)UCHAR_MAX + 1ULL));
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];
    char result;
    int status;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';
    buffer[strcspn(buffer, "\n")] = '\0';

    status = find_summed_character(buffer, sizeof(buffer), &result);
    if (status != 0)
    {
        fprintf(stderr, "Error: invalid or empty input string\n");
        return EXIT_FAILURE;
    }

    printf("Resulting character: %c (ASCII: %d)\n", result, (unsigned char)result);

    return EXIT_SUCCESS;
}