#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm(int a, int b) {
    if (a == 0 || b == 0) {
        return 0;
    }
    return (a / gcd(a, b)) * b;
}

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int lcm_array(int arr[], int size) {
    if (arr == NULL || size <= 0) {
        return 0;
    }
    int result = arr[0];
    for (int i = 1; i < size; i++) {
        result = lcm(result, arr[i]);
        if (result == 0) {
            return 0;
        }
    }
    return result;
}

int main(void) {
    int arr[] = {12, 18, 24, 36};
    int size = sizeof(arr) / sizeof(arr[0]);
    int result = lcm_array(arr, size);
    printf("%d\n", result);
    return 0;
}