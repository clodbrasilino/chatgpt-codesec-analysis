#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  'strerror' is defined in header '<string.h>'; this is probably fixable by adding '#include <string.h>'
  */

int count_integers(const int *list, size_t size, int target)
{
    size_t i;
    int count = 0;
    
    if (list == NULL) {
        errno = EINVAL;
        return -1;
    }
    
    for (i = 0; i < size; i++) {
        if (list[i] == target) {
            if (count < INT_MAX) {
                count++;
            } else {
                errno = ERANGE;
                return -1;
            }
        }
    }
    
    return count;
}

int main(void)
{
    int numbers[] = {1, 2, 3, 2, 4, 2, 5, 2};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    int target = 2;
    int result;
    
    errno = 0;
    result = count_integers(numbers, size, target);
    
    if (result < 0) {
        /* Possible weaknesses found:
         *  implicit declaration of function 'strerror' [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'strerror'
         *  call to undeclared library function 'strerror' with type 'char *(int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        fprintf(stderr, "Error: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }
    
    printf("The integer %d appears %d times in the list.\n", target, result);
    
    return EXIT_SUCCESS;
}