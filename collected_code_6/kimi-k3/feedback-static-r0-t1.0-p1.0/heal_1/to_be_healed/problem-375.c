#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

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
         *  use of undeclared identifier 'INT_MAX'
         *  each undeclared identifier is reported only once for each function it appears in
         *  'INT_MAX' undeclared (first use in this function)
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
         *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
         *  'INT_MIN' undeclared (first use in this function)
         *  use of undeclared identifier 'INT_MIN'
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