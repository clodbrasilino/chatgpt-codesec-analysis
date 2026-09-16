#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 7.256, got 0
  *  test case 2 failed: expected 8.123, got 0
  *  test case 0 failed: expected 4.56, got 0
  */

double tuple_to_float(const char *tuple) {
    const char *start = strchr(tuple, '(');
    if (start == NULL) return 0.0;

    const char *end;
    double result = strtod(start + 1, (char **)&end);

    while (*end == ' ') end++;

    if (*end != ')') return 0.0;

    return result;
}

int main() {
    const char *test_tuples[] = {"(4.56)", "(7.256)", "(8.123)"};
    for (size_t i = 0; i < 3; ++i) {
        double result = tuple_to_float(test_tuples[i]);
        printf("Converted float: %f\n", result);
    }
    return 0;
}