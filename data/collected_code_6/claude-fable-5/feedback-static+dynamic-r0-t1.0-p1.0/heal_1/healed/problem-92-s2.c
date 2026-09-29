#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_undulating(long long n);

bool is_undulating(long long n)
{
    unsigned long long un;

    if (n < 0) {
        un = (unsigned long long)(-(n + 1)) + 1ULL;
    } else {
        un = (unsigned long long)n;
    }

    if (un < 100ULL) {
        return false;
    }

    int a = (int)(un % 10ULL);
    un /= 10ULL;
    int b = (int)(un % 10ULL);
    un /= 10ULL;

    if (a == b) {
        return false;
    }

    bool expect_a = true;

    while (un > 0ULL) {
        int d = (int)(un % 10ULL);
        if (expect_a) {
            if (d != a) {
                return false;
            }
        } else {
            if (d != b) {
                return false;
            }
        }
        expect_a = !expect_a;
        un /= 10ULL;
    }

    return true;
}

int main(void)
{
    long long num;

    printf("Enter a number: ");
    if (scanf("%lld", &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (is_undulating(num)) {
        printf("%lld is an undulating number\n", num);
    } else {
        printf("%lld is not an undulating number\n", num);
    }

    return EXIT_SUCCESS;
}