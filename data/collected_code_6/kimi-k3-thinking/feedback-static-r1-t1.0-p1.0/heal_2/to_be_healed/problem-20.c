#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

int is_woodall(long long num)
{
    long long n;
    long long power;

    if (num < 1)
    {
        return 0;
    }

    n = 1;
    power = 2;

    while (1)
    {
        long long woodall;

        if (power > LLONG_MAX / n)
        {
            break;
        }

        woodall = n * power - 1;

        if (woodall == num)
        {
            return 1;
        }

        if (woodall > num)
        {
            break;
        }

        if (power > LLONG_MAX / 2)
        {
            break;
        }

        power = power * 2;
        n = n + 1;
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    char *endptr;
    long long num;

    printf("Enter a number: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error: failed to read input.\n");
        return 1;
    }

    if (strchr(buffer, '\n') == NULL && !feof(stdin))
    {
        int ch;

        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }

        fprintf(stderr, "Error: input too long.\n");
        return 1;
    }

    errno = 0;
    num = strtoll(buffer, &endptr, 10);

    if (errno == ERANGE || endptr == buffer)
    {
        fprintf(stderr, "Error: invalid input.\n");
        return 1;
    }

    if (*endptr != '\n' && *endptr != '\0')
    {
        fprintf(stderr, "Error: invalid input.\n");
        return 1;
    }

    if (is_woodall(num))
    {
        printf("%lld is a Woodall number.\n", num);
    }
    else
    {
        printf("%lld is not a Woodall number.\n", num);
    }

    return 0;
}