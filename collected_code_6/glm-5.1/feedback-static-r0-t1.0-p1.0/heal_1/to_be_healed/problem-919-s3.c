#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int multiply_items(const int *list, size_t size) {
    if (list == NULL) {
        return 0;
    }

    if (size == 0) {
        return 0;
    }

    long long result = 1;

    for (size_t i = 0; i < size; i++) {
        result *= list[i];
    }

    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MIN'
     *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
     *  'INT_MIN' undeclared (first use in this function)
     *  use of undeclared identifier 'INT_MAX'
     *  each undeclared identifier is reported only once for each function it appears in
     *  'INT_MAX' undeclared (first use in this function)
     */
    if (result > INT_MAX || result < INT_MIN) {
        return 0;
    }

    return (int)result;
}

int main(void) {
    int list1[] = {1, 2, 3, 4, 5};
    size_t size1 = sizeof(list1) / sizeof(list1[0]);

    int res1 = multiply_items(list1, size1);
    printf("%d\n", res1);

    int list2[] = {0, 2, 3};
    size_t size2 = sizeof(list2) / sizeof(list2[0]);

    int res2 = multiply_items(list2, size2);
    printf("%d\n", res2);

    int res3 = multiply_items(NULL, size2);
    printf("%d\n", res3);

    int res4 = multiply_items(list1, 0);
    printf("%d\n", res4);

    return 0;
}