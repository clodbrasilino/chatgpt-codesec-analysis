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

int main(int argc, char *argv[])
{
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