#include <stdio.h>
#include <stdlib.h>

long long countIntegralPoints(long long x1, long long y1, long long x2, long long y2);
 /* Possible weaknesses found:
  *  test case 1 failed: expected 1, got 0
  */

long long countIntegralPoints(long long x1, long long y1, long long x2, long long y2)
{
    long long dx;
    long long dy;

    if (x2 < x1)
    {
        long long tmp = x1;
        x1 = x2;
        x2 = tmp;
    }

    /* Possible weaknesses found:
     *  Assuming that condition 'y2<y1' is not redundant
     */
    if (y2 < y1)
    {
        /* Possible weaknesses found:
         *  tmp is assigned 'y1' here.
         */
        long long tmp = y1;
        /* Possible weaknesses found:
         *  y1 is assigned 'y2' here.
         */
        y1 = y2;
        /* Possible weaknesses found:
         *  y2 is assigned 'tmp' here.
         */
        y2 = tmp;
    }

    dx = x2 - x1;
    /* Possible weaknesses found:
     *  Assignment 'dy=y2-y1', assigned value is less than 2
     */
    dy = y2 - y1;

    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (dx != dy)
    {
        return -1;
    }

    /* Possible weaknesses found:
     *  Condition 'dx<=1' is always true
     *  Condition 'dx<=1' is always true [knownConditionTrueFalse]
     */
    if (dx <= 1)
    {
        return 0;
    }

    return (dx - 1) * (dy - 1);
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
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    printf("Enter top-right corner (x2 y2): ");
    if (scanf("%lld %lld", &x2, &y2) != 2)
    {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    result = countIntegralPoints(x1, y1, x2, y2);

    if (result < 0)
    {
        fprintf(stderr, "The given coordinates do not form a valid axis-aligned square.\n");
        return EXIT_FAILURE;
    }

    printf("Number of integral coordinates strictly inside the square: %lld\n", result);

    return EXIT_SUCCESS;
}