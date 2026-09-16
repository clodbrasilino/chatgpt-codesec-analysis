#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got <no output>
  *  test case 1 failed: expected True, got <no output>
  *  test case 0 failed: expected True, got <no output>
  */

bool is_product_even(const int arr[], int n) {
    if (n <= 0) {
        return false;
    }
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            return true;
        }
    }
    return false;
}

int main(void) {
    int arr[] = {1, 3, 5, 7, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    if (is_product_even(arr, n)) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    return 0;
}