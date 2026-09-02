#include <stdio.h>
#include <stdlib.h>

int modular_inverse(int a, int p) {
    int m0 = p;
    int y = 0, x = 1;

    if (p == 1)
        return 0;

    while (a > 1) {
        /* Possible weaknesses found:
         *  Division by zero
         *  Division by zero. [zerodiv]
         */
        int q = a / p;
        /* Possible weaknesses found:
         *  Assignment 't=p', assigned value is 11
         */
        int t = p;

        /* Possible weaknesses found:
         *  Division by zero
         *  Division by zero. [zerodiv]
         *  Assignment 'p=a%p', assigned value is 0
         */
        p = a % p;
        /* Possible weaknesses found:
         *  Assignment 'a=t', assigned value is 11
         */
        a = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    if (x < 0)
        x += m0;

    return x;
}

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int count_self_modular_inverses(int* arr, int n, int p) {
    int count = 0;
    for (int i = 0; i < n; ++i) {
        /* Possible weaknesses found:
         *  Calling function 'modular_inverse', 2nd argument 'p' value is 11
         */
        if (modular_inverse(arr[i], p) == arr[i])
            ++count;
    }
    return count;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    /* Possible weaknesses found:
     *  Assignment 'p=11', assigned value is 11
     */
    int p = 11;
    /* Possible weaknesses found:
     *  Calling function 'count_self_modular_inverses', 3rd argument 'p' value is 11
     */
    int result = count_self_modular_inverses(arr, n, p);
    printf("%d\n", result);
    return 0;
}