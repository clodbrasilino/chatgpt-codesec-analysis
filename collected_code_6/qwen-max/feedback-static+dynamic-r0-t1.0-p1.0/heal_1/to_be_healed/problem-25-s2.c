#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
unsigned long long productOfNonRepeatedElements(int *arr, size_t len) {
    unsigned long long product = 1;
    int found[1001] = {0};

    for (size_t i = 0; i < len; ++i) {
        if (found[arr[i]] == 0) {
            product *= arr[i];
        }
        found[arr[i]]++;
    }

    return product;
}

int main() {
    int arr[] = {2, 3, 4, 4, 1, 1, 2};
    size_t len = sizeof(arr) / sizeof(arr[0]);

    unsigned long long result = productOfNonRepeatedElements(arr, len);

    printf("Product of non-repeated elements: %llu\n", result);

    return 0;
}