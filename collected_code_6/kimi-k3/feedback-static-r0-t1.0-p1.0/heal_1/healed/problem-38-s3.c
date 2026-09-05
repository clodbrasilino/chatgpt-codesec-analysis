#include <stdio.h>
#include <stdlib.h>

double divide_first_even_odd(const int *arr, int size) {
    int first_even = 0, first_odd = 0;
    int even_found = 0, odd_found = 0;
    
    if (arr == NULL || size <= 0) {
        return 0.0;
    }
    
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0 && !even_found) {
            first_even = arr[i];
            even_found = 1;
        } else if (arr[i] % 2 != 0 && !odd_found) {
            first_odd = arr[i];
            odd_found = 1;
        }
        
        if (even_found && odd_found) {
            break;
        }
    }
    
    if (!even_found || !odd_found || first_odd == 0) {
        return 0.0;
    }
    
    return (double)first_even / first_odd;
}

int main() {
    int arr[] = {3, 7, 8, 12, 5, 10};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    double result = divide_first_even_odd(arr, size);
    
    if (result != 0.0) {
        printf("Result: %.2f\n", result);
    } else {
        printf("Cannot perform division\n");
    }
    
    return 0;
}