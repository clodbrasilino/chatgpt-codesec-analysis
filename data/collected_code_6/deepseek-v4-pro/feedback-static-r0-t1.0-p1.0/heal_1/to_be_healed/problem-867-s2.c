#include <stdio.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int min_number_to_make_even_sum(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    if (sum % 2 == 0) {
        return 0;
    }
    return 1;
}

int main(void) {
    int n;
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input\n");
        return 1;
    }
    
    int arr[100];
    if (n > 100) {
        printf("Array size too large\n");
        return 1;
    }
    
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("Invalid input\n");
            return 1;
        }
    }
    
    int result = min_number_to_make_even_sum(arr, n);
    printf("Minimum number to add: %d\n", result);
    
    return 0;
}