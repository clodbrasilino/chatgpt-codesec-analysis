#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int calculate_difference(int n, long long *result)
{
    long long sum;
    long long sum_of_squares;

    if (result == NULL)
    {
        return -1;
    }

    if (n < 1)
    {
        return -1;
    }

    sum = (long long)n * (n + 1) / 2;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1698267891574638162 * -1688615139 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:21910,execs:10038,op:havoc,rep:8)
     * UBSan: signed integer overflow: 2 * 1303176078 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000001,time:21910,execs:10038,op:havoc,rep:8)
     * UBSan: signed integer overflow: 12345679098765432 * 222222223 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:1857,execs:870,op:havoc,rep:2)
     */
    sum_of_squares = (long long)n * (n + 1) * (2 * n + 1) / 6;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 6172839549382716 * 6172839549382716 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:1857,execs:870,op:havoc,rep:2)
     * UBSan: signed integer overflow: 849133945787319081 * 849133945787319081 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:21910,execs:10038,op:havoc,rep:8)
     * UBSan: signed integer overflow: 4989855151 * 4989855151 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000004,time:3580,execs:1718,op:havoc,rep:7)
     */
    *result = sum * sum - sum_of_squares;

    return 0;
}

int main(void)
{
    int n;
    long long difference;
    int status;

    printf("Enter a positive integer: ");
    
    if (scanf("%d", &n) != 1)
    {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }

    status = calculate_difference(n, &difference);
    
    if (status != 0)
    {
        fprintf(stderr, "Error: Invalid input or calculation failed\n");
        return EXIT_FAILURE;
    }

    printf("Difference: %lld\n", difference);

    return EXIT_SUCCESS;
}