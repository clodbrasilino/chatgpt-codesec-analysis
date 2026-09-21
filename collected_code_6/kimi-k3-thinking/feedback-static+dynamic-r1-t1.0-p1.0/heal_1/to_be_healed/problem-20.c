#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got <no output>
  *  test case 0 failed: expected True, got <no output>
  *  test case 1 failed: expected False, got <no output>
  */

int is_woodall(long long num)
{
    long long n;
    long long power;
    /* Possible weaknesses found:
     *  The scope of the variable 'woodall' can be reduced. [variableScope]
     */
    long long woodall;

    if (num < 1)
    {
        return 0;
    }

    n = 1;
    power = 2;

    while (1)
    {
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