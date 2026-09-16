#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 2664, got 0
  *  test case 1 failed: expected 273, got 0
  *  test case 0 failed: expected 30, got 1
  */

int is_smart_number(long long num)
{
    if (num <= 0) {
        return 0;
    }
    if (num == 1) {
        return 1;
    }
    if (num % 2 == 0 || num % 3 == 0 || num % 5 == 0 || num % 7 == 0) {
        return 0;
    }
    return 1;
}

long long find_nth_smart_number(int n)
{
    if (n <= 0) {
        return -1;
    }
    long long count = 0;
    long long num = 1;
    while (count < n) {
        if (is_smart_number(num)) {
            count++;
            if (count == n) {
                return num;
            }
        }
        num++;
    }
    return -1;
}

int main(void)
{
    int n;
    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }
    long long result = find_nth_smart_number(n);
    if (result == -1) {
        return EXIT_FAILURE;
    }
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}