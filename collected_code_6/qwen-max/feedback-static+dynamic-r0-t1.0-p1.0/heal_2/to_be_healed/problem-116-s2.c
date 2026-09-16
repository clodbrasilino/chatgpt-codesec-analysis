#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 456, got <no output>
  *  test case 0 failed: expected 123, got <no output>
  *  test case 2 failed: expected 567, got <no output>
  */

long long tupleToInt(const int *tuple, int size) {
    long long result = 0;
    for (int i = 0; i < size; ++i) {
        result = result * 10 + tuple[i];
    }
    return result;
}

int main() {
    int tuple[] = {1, 2, 3, 4, 5};
    int size = sizeof(tuple) / sizeof(tuple[0]);
    long long result = tupleToInt(tuple, size);
    printf("%lld\n", result);
    return 0;
}