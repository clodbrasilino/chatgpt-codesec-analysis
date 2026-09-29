#include <stdio.h>
#include <stdbool.h>

static bool is_present(long long first, long long diff, long long target)
{
    long long offset;

    if (diff == 0LL) {
        return (first == target);
    }

    offset = target - first;

    if (offset % diff != 0LL) {
        return false;
    }

    return (offset / diff) >= 0LL;
}

int main(void)
{
    long long first;
    long long diff;
    long long target;
    int scanned;

    scanned = scanf("%lld %lld %lld", &first, &diff, &target);
    if (scanned != 3) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (is_present(first, diff, target)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}