#include <stdio.h>
#include <math.h>

void nthPower(int arr[], int size, int n) {
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        arr[i] = pow(arr[i], n);
    }
}

int main() {
    int size, n;
    printf("Enter the size of the list: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'size' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &size);

    int arr[size];
    printf("Enter the elements of the list: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the power to raise each element: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'n' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &n);

    nthPower(arr, size, n);

    printf("List after raising each element to the %d-th power:\n", n);
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized [premium-bughuntingUninit]
         */
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}