#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 1, got 0
  */

long long countIntegralPoints(long long x1, long long y1, long long x2, long long y2)
{
    long long side_x;
    long long side_y;

    side_x = x2 - x1;
    if (side_x < 0)
    {
        side_x = -side_x;
    }

    side_y = y2 - y1;
    if (side_y < 0)
    {
        side_y = -side_y;
    }

    if (side_x != side_y)
    {
        return -1;
    }

    if (side_x < 2)
    {
        return 0;
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775802 * 9223372036854775802 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:13977,execs:9059,op:havoc,rep:2)
     */
    return (side_x - 1) * (side_x - 1);
}

int main(void)
{
    long long x1;
    long long y1;
    long long x2;
    long long y2;
    long long result;

    printf("Enter bottom-left corner (x1 y1): ");
    if (scanf("%lld %lld", &x1, &y1) != 2)
    {
        fprintf(stderr, "Invalid input for first corner\n");
        return EXIT_FAILURE;
    }

    printf("Enter top-right corner (x2 y2): ");
    if (scanf("%lld %lld", &x2, &y2) != 2)
    {
        fprintf(stderr, "Invalid input for second corner\n");
        return EXIT_FAILURE;
    }

    result = countIntegralPoints(x1, y1, x2, y2);
    if (result < 0)
    {
        fprintf(stderr, "The given coordinates do not form a square\n");
        return EXIT_FAILURE;
    }

    printf("Number of integral coordinates inside the square: %lld\n", result);

    return EXIT_SUCCESS;
}