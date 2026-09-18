#include <stdio.h>

float division(int arr[], int n) {
    int first_odd = 0, first_even = 0, i = 0;
   
    while(i < n) {
        if(arr[i] % 2 == 0 && first_even == 0) {
            first_even = arr[i];
        } else if(arr[i] % 2 != 0 && first_odd == 0) {
            first_odd = arr[i];
        }

        if(first_odd != 0 && first_even != 0) {
            break;
        }
        i++;
    }

    if(first_odd == 0) {
        printf("division by zero is not allowed\n");
        return 0;
    }
    
    return (float)first_even / (float)first_odd;
}

int main() {
    int arr[] = {5, 4, 9, 8, 7, 1, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Division of even by odd is: %f\n", division(arr, n));
    return 0;
}