#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int sum_positive(const int *array, size_t size) {
    if (array == NULL) {
        return 0;
    }

    int sum = 0;
    for (size_t i = 0; i < size; ++i) {
        if (array[i] > 0) {
            /* Possible weaknesses found:
             *  use of undeclared identifier 'INT_MAX'
             *  'INT_MAX' undeclared (first use in this function)
             *  each undeclared identifier is reported only once for each function it appears in
             */
            if (array[i] > INT_MAX - sum) {
                return 0;
            }
            sum += array[i];
        }
    }
    return sum;
}

int main(void) {
    int data[] = {-3, 5, -2, 12, 0, -8, 7};
    size_t data_size = sizeof(data) / sizeof(data[0]);

    int result = sum_positive(data, data_size);
    printf("%d\n", result);

    return 0;
}