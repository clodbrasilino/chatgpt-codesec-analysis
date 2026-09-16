#include <stdio.h>
#include <stdlib.h>

int find_division(const int *list, size_t size, double *result)
{
    int even = 0;
    int odd = 0;
    int even_found = 0;
    int odd_found = 0;
    size_t i;

    if ((list == NULL) || (result == NULL) || (size == 0U)) {
        return -1;
    }

    for (i = 0U; i < size; i++) {
        if (((list[i] % 2) == 0) && (even_found == 0)) {
            even = list[i];
            even_found = 1;
        }
        if (((list[i] % 2) != 0) && (odd_found == 0)) {
            odd = list[i];
            odd_found = 1;
        }
        if ((even_found == 1) && (odd_found == 1)) {
            break;
        }
    }

    if ((even_found == 0) || (odd_found == 0)) {
        return -1;
    }

    if (odd == 0) {
        return -1;
    }

    *result = (double)even / (double)odd;
    return 0;
}

int main(void)
{
    int list[] = {1, 3, 5, 7, 4, 1, 6, 8};
    size_t size = sizeof(list) / sizeof(list[0]);
    double result = 0.0;

    if (find_division(list, size, &result) == 0) {
        if (printf("Division of first even and odd number: %f\n", result) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (fprintf(stderr, "Could not compute division\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}