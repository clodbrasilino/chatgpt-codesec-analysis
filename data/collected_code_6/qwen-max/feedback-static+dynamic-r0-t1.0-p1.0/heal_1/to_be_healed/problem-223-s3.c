#include <stdio.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
bool has_majority(int *arr, int n) {
    if (n == 0) return false;
    int candidate = arr[0];
    int count = 1;
    for (int i = 1; i < n; ++i) {
        /* Possible weaknesses found:
         *  first condition
         */
        if (arr[i] == candidate) {
            count++;
            if (count > n / 2) return true;
        /* Possible weaknesses found:
         *  Expression is always true because 'else if' condition is opposite to previous condition at line 9. [multiCondition]
         *  else if condition is opposite to first condition
         */
        } else if (arr[i] != candidate) {
            candidate = arr[i];
            count = 1;
        }
    }
    return false;
}

int main() {
    int arr[] = {1, 1, 2, 3, 3, 3, 3, 4, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    if (has_majority(arr, n)) {
        printf("Array has a majority element.\n");
    } else {
        printf("Array does not have a majority element.\n");
    }
    return 0;
}