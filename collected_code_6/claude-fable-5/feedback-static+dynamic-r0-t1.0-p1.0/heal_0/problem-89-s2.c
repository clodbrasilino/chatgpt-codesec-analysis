#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int closest_smaller(int n, int *result)
{
    if (result == NULL) {
        return -1;
    }
    if (n == INT_MIN) {
        return -1;
    }
    *result = n - 1;
    return 0;
}

int main(void)
{
    int values[] = { 10, 0, -5, INT_MIN, INT_MAX };
    size_t count = sizeof(values) / sizeof(values[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        int result = 0;
        if (closest_smaller(values[i], &result) == 0) {
            if (printf("Closest smaller than %d is %d\n", values[i], result) < 0) {
                return EXIT_FAILURE;
            }
        } else {
            if (printf("No smaller value exists for %d\n", values[i]) < 0) {
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}