#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

int is_abundant(unsigned long long n)
{
    if (n == 0)
    {
        return 0;
    }

    unsigned long long sum = 1;
    unsigned long long i;

    for (i = 2; i <= n / i; i++)
    {
        if (n % i == 0)
        {
            sum += i;
            if (i != n / i)
            {
                sum += n / i;
            }
        }
    }

    return sum > n;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64];
    char *endptr;
    unsigned long long number;
    size_t len;

    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    if (memchr(input, '\0', sizeof(input)) == NULL)
    {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] != '\n' && !feof(stdin))
    {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoull(input, &endptr, 10);

    if (errno == ERANGE || endptr == input || (*endptr != '\n' && *endptr != '\0'))
    {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (is_abundant(number))
    {
        printf("%llu is abundant\n", number);
    }
    else
    {
        printf("%llu is not abundant\n", number);
    }

    return EXIT_SUCCESS;
}