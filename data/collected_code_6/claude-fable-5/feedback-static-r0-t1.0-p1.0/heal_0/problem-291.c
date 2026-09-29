#include <stdio.h>
#include <stdlib.h>

static unsigned long long countWays(int n, int k);

static unsigned long long countWays(int n, int k)
{
    unsigned long long same;
    unsigned long long diff;
    unsigned long long total;
    int i;

    if (n <= 0 || k <= 0) {
        return 0ULL;
    }

    if (n == 1) {
        return (unsigned long long)k;
    }

    same = (unsigned long long)k;
    diff = (unsigned long long)k * (unsigned long long)(k - 1);
    total = same + diff;

    for (i = 3; i <= n; i++) {
        same = diff;
        diff = total * (unsigned long long)(k - 1);
        total = same + diff;
    }

    return total;
}

int main(void)
{
    int n;
    int k;
    unsigned long long result;

    n = 0;
    k = 0;

    printf("Enter number of posts: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input for number of posts.\n");
        return EXIT_FAILURE;
    }

    printf("Enter number of colors: ");
    if (scanf("%d", &k) != 1) {
        fprintf(stderr, "Invalid input for number of colors.\n");
        return EXIT_FAILURE;
    }

    if (n <= 0 || k <= 0) {
        fprintf(stderr, "Both posts and colors must be positive integers.\n");
        return EXIT_FAILURE;
    }

    result = countWays(n, k);

    printf("Number of ways to paint the fence: %llu\n", result);

    return EXIT_SUCCESS;
}