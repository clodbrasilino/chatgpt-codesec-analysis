#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int is_woodall(unsigned long long x)
{
    unsigned long long n;
    unsigned long long value;

    if (x < 1ULL) {
        return 0;
    }

    for (n = 1ULL; n < 64ULL; n++) {
        if (n > (ULLONG_MAX >> n)) {
            break;
        }
        value = n << n;
        if (value - 1ULL == x) {
            return 1;
        }
        if (value - 1ULL > x) {
            break;
        }
    }

    return 0;
}

int main(void)
{
    unsigned long long num;
    int result;

    printf("Enter a non-negative integer: ");
    result = scanf("%llu", &num);
    if (result != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (is_woodall(num)) {
        printf("%llu is a Woodall number.\n", num);
    } else {
        printf("%llu is not a Woodall number.\n", num);
    }

    return EXIT_SUCCESS;
}