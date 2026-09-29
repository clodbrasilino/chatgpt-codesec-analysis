#include <stdio.h>
#include <stdbool.h>

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

bool isModInverseEqual(int num, int p) {
    if (gcd(num, p) == 1) {
        return (num * num) % p == 1;
    }
    return false;
}

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int countSelfModInverse(int *arr, int size, int p) {
    int count = 0;
    for (int i = 0; i < size; ++i) {
        if (isModInverseEqual(arr[i], p)) {
            ++count;
        }
    }
    return count;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6};
    int size = sizeof(arr) / sizeof(arr[0]);
    int p = 7;
    int result = countSelfModInverse(arr, size, p);
    printf("%d\n", result);
    return 0;
}