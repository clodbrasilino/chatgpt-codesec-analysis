#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 8.123, got 0
  *  test case 1 failed: expected 7.256, got 0
  *  test case 0 failed: expected 4.56, got 0
  */

double tuple_to_float(const char *tuple) {
    char *end;
    const char *start = strchr(tuple, '(');
    if (start == NULL) return 0.0;

    start++;
    char *buffer = (char *)malloc(strlen(start) + 1);
    if (buffer == NULL) return 0.0;

    strncpy(buffer, start, strlen(start));
    buffer[strlen(start)] = '\0';

    double result = strtod(buffer, &end);
    free(buffer);

    if (end == buffer || *end != ')') return 0.0;

    return result;
}

int main() {
    const char *test_tuple = "(3.14)";
    double result = tuple_to_float(test_tuple);
    printf("Converted float: %f\n", result);
    return 0;
}