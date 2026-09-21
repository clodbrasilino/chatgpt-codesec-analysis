#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int is_woodall(long long num)
{
    long long n = 1;
    long long power = 2;

    if (num < 1)
    {
        return 0;
    }

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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    const char *input;
    char *endptr;
    long long num;

    if (argc > 1)
    {
        input = argv[1];
    }
    else
    {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        {
            fprintf(stderr, "Error: failed to read input.\n");
            return 1;
        }
        input = buffer;
    }

    errno = 0;
    num = strtoll(input, &endptr, 10);

    if (errno == ERANGE || endptr == input)
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
        printf("True\n");
    }
    else
    {
        printf("False\n");
    }

    return 0;
}