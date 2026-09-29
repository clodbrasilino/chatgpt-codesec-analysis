#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
int find_product(int *list, size_t size, int *result) {
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
        return -1;
    }

    *result = first_even * first_odd;
    return 0;
}

int main(void) {
    int list[] = {5, 8, 3, 12, 7};
    size_t size = sizeof(list) / sizeof(list[0]);
    int result;

    if (find_product(list, size, &result) == 0) {
        printf("%d\n", result);
    } else {
        printf("Invalid input or missing even/odd numbers\n");
    }

    return 0;
}