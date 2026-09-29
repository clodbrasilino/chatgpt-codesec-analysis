#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int round_to_multiple(int number, int multiple, int *result)
{
    if (result == NULL)
    {
        return -1;
    }
    
    if (multiple == 0)
    {
        return -1;
    }
    
    if (number > 0)
    {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2147483647 - -11 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000005,time:4179,execs:1578,op:havoc,rep:3)
         */
        if (number > INT_MAX - multiple / 2)
        {
            return -1;
        }
        *result = ((number + multiple / 2) / multiple) * multiple;
    }
    else
    {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -2147483648 + -11111111 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000004,time:2527,execs:970,op:havoc,rep:7)
         */
        if (number < INT_MIN + multiple / 2)
        {
            return -1;
        }
        *result = ((number - multiple / 2) / multiple) * multiple;
    }
    
    return 0;
}

int main(void)
{
    int number = 0;
    int multiple = 0;
    int result = 0;
    int status = 0;
    
    printf("Enter number: ");
    if (scanf("%d", &number) != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter multiple: ");
    if (scanf("%d", &multiple) != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    status = round_to_multiple(number, multiple, &result);
    if (status != 0)
    {
        fprintf(stderr, "Error: invalid multiple or overflow\n");
        return EXIT_FAILURE;
    }
    
    printf("Result: %d\n", result);
    
    return EXIT_SUCCESS;
}