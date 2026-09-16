#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 456, got <no output>
  *  test case 0 failed: expected 123, got <no output>
  *  test case 2 failed: expected 567, got <no output>
  */

int tuple_to_int(const int *tuple, size_t length) {
    int result = 0;
    for (size_t i = 0; i < length; ++i) {
        result += tuple[i] * (10 * (length - i - 1));
    }
    return result;
}

int main() {
    int tuple1[] = {1, 2, 3};
    size_t length1 = sizeof(tuple1) / sizeof(tuple1[0]);
    int result1 = tuple_to_int(tuple1, length1);
    printf("%d\n", result1);

    int tuple2[] = {4, 5, 6};
    size_t length2 = sizeof(tuple2) / sizeof(tuple2[0]);
    int result2 = tuple_to_int(tuple2, length2);
    printf("%d\n", result2);

    int tuple3[] = {5, 6, 7};
    size_t length3 = sizeof(tuple3) / sizeof(tuple3[0]);
    int result3 = tuple_to_int(tuple3, length3);
    printf("%d\n", result3);

    return 0;
}