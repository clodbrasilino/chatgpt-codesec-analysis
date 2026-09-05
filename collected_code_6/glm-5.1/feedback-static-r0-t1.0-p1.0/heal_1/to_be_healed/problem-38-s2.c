#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
int find_division(int *list, size_t size, double *result) {
    if (list == NULL || result == NULL || size == 0) {
        return -1;
    }

    int first_even = 0;
    int first_odd = 0;
    int even_found = 0;
    int odd_found = 0;

    for (size_t i = 0; i < size; i++) {
        if (!even_found && list[i] % 2 == 0) {
            first_even = list[i];
            even_found = 1;
        } else if (!odd_found && list[i] % 2 != 0) {
            first_odd = list[i];
            odd_found = 1;
        }

        if (even_found && odd_found) {
            break;
        }
    }

    if (!even_found || !odd_found) {
        return -2;
    }

    if (first_even == 0 || first_odd == 0) {
        return -3;
    }

    *result = (double)first_even / (double)first_odd;

    return 0;
}

int main(void) {
    int list[] = {5, 8, 12, 3, 7};
    size_t size = sizeof(list) / sizeof(list[0]);
    double result = 0.0;

    int ret = find_division(list, size, &result);

    if (ret == 0) {
        printf("%f\n", result);
    } else {
        printf("Error code: %d\n", ret);
    }

    return 0;
}