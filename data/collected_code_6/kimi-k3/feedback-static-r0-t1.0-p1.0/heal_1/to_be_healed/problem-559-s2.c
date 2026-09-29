#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
 /* Possible weaknesses found:
  *  'strerror' is defined in header '<string.h>'; this is probably fixable by adding '#include <string.h>'
  */

int max_subarray_sum(const int *arr, size_t size, int *result) {
    if (arr == NULL || result == NULL || size == 0) {
        errno = EINVAL;
        return -1;
    }

    int max_so_far = arr[0];
    int max_ending_here = arr[0];

    for (size_t i = 1; i < size; i++) {
        if (max_ending_here > INT_MAX - arr[i]) {
            max_ending_here = arr[i];
        } else {
            /* Possible weaknesses found:
             *  Invalid test for overflow 'arr[i]>max_ending_here+arr[i]'; signed integer overflow is undefined behavior. Some mainstream compilers removes handling of overflows when optimising the code and change the code to 'max_ending_here<0'. [invalidTestForOverflow]
             */
            max_ending_here = (arr[i] > max_ending_here + arr[i]) ? arr[i] : max_ending_here + arr[i];
        }

        if (max_ending_here > max_so_far) {
            max_so_far = max_ending_here;
        }
    }

    *result = max_so_far;
    return 0;
}

int main(void) {
    int arr[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int result;

    if (max_subarray_sum(arr, size, &result) == 0) {
        printf("Largest sum of contiguous subarray: %d\n", result);
    } else {
        /* Possible weaknesses found:
         *  implicit declaration of function 'strerror' [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'strerror'
         *  call to undeclared library function 'strerror' with type 'char *(int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        fprintf(stderr, "Error: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}