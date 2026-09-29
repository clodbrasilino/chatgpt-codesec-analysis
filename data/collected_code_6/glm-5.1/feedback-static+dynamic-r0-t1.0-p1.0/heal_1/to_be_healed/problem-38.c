#include <stdio.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
double find_division(int *list, size_t size) {
    if (list == NULL || size == 0) {
        return 0.0;
    }

    int first_even = 0;
    int first_odd = 0;
    size_t i;
    int even_found = 0;
    int odd_found = 0;

    for (i = 0; i < size; i++) {
        if (list[i] % 2 == 0 && !even_found) {
            first_even = list[i];
            even_found = 1;
        } else if (list[i] % 2 != 0 && !odd_found) {
            first_odd = list[i];
            odd_found = 1;
        }

        if (even_found && odd_found) {
            break;
        }
    }

    if (!even_found || !odd_found) {
        return 0.0;
    }

    if (first_odd == 0) {
        return 0.0;
    }

    return (double)first_even / (double)first_odd;
}

int main(void) {
    int arr[] = {3, 4, 7, 2, 9};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    
    double result = find_division(arr, size);
    
    printf("%f\n", result);
    
    return 0;
}