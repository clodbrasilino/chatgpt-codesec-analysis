#include <stdio.h>

int findProduct(int arr[], int size) {
    // Initialize product as 1
    int product = 1;

    // Iterate through the array
    for (int i = 0; i < size; i++) {
        int count = 0;

        // Check if the element has repeated occurences
        for (int j = 0; j < size; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'arr[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (arr[i] == arr[j])
                count++;
        }
        
        // If the element is non-repeated, multiply it with the product
        if (count == 1)
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            product *= arr[i];
    }

    return product;
}

int main() {
    // Test the function
    int arr[] = {5, 7, 2, 7, 3, 2, 6};
    int size = sizeof(arr) / sizeof(arr[0]);

    int result = findProduct(arr, size);
    printf("Product of non-repeated elements: %d", result);

    return 0;
}