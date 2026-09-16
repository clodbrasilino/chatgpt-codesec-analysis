#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool is_undulating(long long num)
{
    if (num < 0) {
        num = -num;
    }

    if (num < 100) {
        return false;
    }

    int first = (int)(num % 10);
    num /= 10;
    int second = (int)(num % 10);
    num /= 10;

    if (first == second) {
        return false;
    }

    bool expect_first = true;
    while (num > 0) {
        int digit = (int)(num % 10);
        if (expect_first) {
            if (digit != first) {
                return false;
            }
        } else {
            if (digit != second) {
                return false;
            }
        }
        expect_first = !expect_first;
        num /= 10;
    }

    return true;
}

int main(void)
{
    long long tests[] = {121212LL, 1212121LL, 1991LL, 101LL, 12LL, 3434343LL, 1234LL};
    size_t count = sizeof(tests) / sizeof(tests[0]);

    for (size_t i = 0; i < count; i++) {
        if (printf("%lld is %sundulating\n", tests[i],
                   is_undulating(tests[i]) ? "" : "not ") < 0) {
            return EXIT_FAILURE;
        }
    }

    long long input = 0;
    if (printf("Enter a number: ") < 0) {
        return EXIT_FAILURE;
    }
    if (scanf("%lld", &input) != 1) {
        if (fprintf(stderr, "Invalid input\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("%lld is %sundulating\n", input,
               is_undulating(input) ? "" : "not ") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}