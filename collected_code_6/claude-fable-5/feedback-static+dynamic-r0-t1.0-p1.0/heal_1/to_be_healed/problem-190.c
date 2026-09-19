#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 1, got 0
  */

long long countIntegralPoints(long long x1, long long y1, long long x2, long long y2)
{
    long long width;
    long long height;

    if (x2 > x1)
    {
        width = x2 - x1;
    }
    else
    {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223372036854775807 - -21 cannot be represented in type 'long long' (AFL crash: id:000004,sig:06,src:000002,time:59304,execs:35579,op:havoc,rep:3)
         */
        width = x1 - x2;
    }

    if (y2 > y1)
    {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223372036854775807 - -2 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000002,time:46136,execs:28014,op:havoc,rep:6)
         */
        height = y2 - y1;
    }
    else
    {
        height = y1 - y2;
    }

    if (width < 2 || height < 2)
    {
        return 0;
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 111111106 * 9223372036854775805 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:1017,execs:682,op:havoc,rep:5)
     * UBSan: signed integer overflow: 9223372036854775805 * 2 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:5337,execs:3470,op:havoc,rep:1)
     * UBSan: signed integer overflow: 2 * 9223372036854775802 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:5666,execs:3682,op:havoc,rep:1)
     */
    return (width - 1) * (height - 1);
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
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Enter top-right corner (x2 y2): ");
    if (scanf("%lld %lld", &x2, &y2) != 2)
    {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    result = countIntegralPoints(x1, y1, x2, y2);
    printf("Number of integral coordinates inside the square: %lld\n", result);

    return EXIT_SUCCESS;
}