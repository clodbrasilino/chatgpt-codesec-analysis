#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 5, got 1
  *  test case 0 failed: expected 2, got 1
  *  test case 2 failed: expected 15, got 1
  */

unsigned long long bell_number(int n)
{
    if (n < 0) {
        return 0;
    }

    unsigned long long *bell = (unsigned long long *)calloc((size_t)n + 2, sizeof(unsigned long long));
    if (bell == NULL) {
        return 0;
    }

    bell[0] = 1;

    for (int i = 1; i <= n; i++) {
        bell[i] = bell[i - 1];
        for (int j = i - 1; j >= 1; j--) {
            bell[j] = bell[j] + bell[j - 1];
        }
        bell[0] = bell[i];
    }

    unsigned long long result = bell[0];
    free(bell);
    return result;
}

int main(void)
{
    int n;
    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }
    printf("%llu\n", bell_number(n));
    return EXIT_SUCCESS;
}