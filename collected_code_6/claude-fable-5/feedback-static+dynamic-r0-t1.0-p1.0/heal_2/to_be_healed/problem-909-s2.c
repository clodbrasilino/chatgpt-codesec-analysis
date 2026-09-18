#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int is_palindrome(long long num)
{
    long long reversed = 0;
    long long original = num;
    /* Possible weaknesses found:
     *  The scope of the variable 'digit' can be reduced. [variableScope]
     */
    long long digit;

    if (num < 0LL) {
        return 0;
    }

    while (num > 0LL) {
        digit = num % 10LL;

        if (reversed > (LLONG_MAX - digit) / 10LL) {
            return 0;
        }

        reversed = (reversed * 10LL) + digit;
        num /= 10LL;
    }

    return (reversed == original) ? 1 : 0;
}

static int previous_palindrome(long long num, long long *result)
{
    long long candidate;

    if (result == NULL) {
        return -1;
    }

    if (num <= 0LL) {
        return -1;
    }

    for (candidate = num - 1LL; candidate >= 0LL; candidate--) {
        if (is_palindrome(candidate)) {
            *result = candidate;
            return 0;
        }
        if (candidate == 0LL) {
            break;
        }
    }

    return -1;
}

int main(void)
{
    long long input = 0LL;
    long long palindrome = 0LL;
    int scan_status;

    printf("Enter a number: ");
    scan_status = scanf("%lld", &input);

    if (scan_status != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (previous_palindrome(input, &palindrome) != 0) {
        fprintf(stderr, "Error: no previous palindrome exists for %lld.\n", input);
        return EXIT_FAILURE;
    }

    printf("The previous palindrome of %lld is %lld\n", input, palindrome);

    return EXIT_SUCCESS;
}