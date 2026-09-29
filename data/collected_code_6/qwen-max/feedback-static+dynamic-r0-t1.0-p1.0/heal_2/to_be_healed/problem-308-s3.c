#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list2' can be declared as pointer to const [constParameterPointer]
 */
void findLargestProducts(int *list1, int *list2, int size, int n, long long *result) {
    long long products[size * size];
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            products[i * size + j] = (long long)list1[i] * list2[j];
        }
    }

    for (int i = 0; i < size * size - 1; ++i) {
        for (int j = 0; j < size * size - 1 - i; ++j) {
            if (products[j] < products[j + 1]) {
                long long temp = products[j];
                products[j] = products[j + 1];
                products[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        /* Possible weaknesses found:
         *  Uninitialized variable: products [uninitvar]
         */
        result[i] = products[i];
    }
}

int main() {
    int list1[] = {1, 2, 3};
    int list2[] = {4, 5, 6};
    int size = 3;
    int n = 2;
    long long result[n];

    findLargestProducts(list1, list2, size, n, result);

    for (int i = 0; i < n; ++i) {
        printf("%lld\n", result[i]);
    }

    return 0;
}