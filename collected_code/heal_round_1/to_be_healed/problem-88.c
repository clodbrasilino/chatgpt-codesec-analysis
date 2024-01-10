#include <stdio.h>
#define MAX_SIZE 100

void getFrequency(int arr[], int size) {
    int count[MAX_SIZE] = {0};

    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        count[arr[i]]++;
    }

    printf("Frequency of elements in the array:\n");
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (count[arr[i]] != 0) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            printf("%d: %d\n", arr[i], count[arr[i]]);
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            count[arr[i]] = 0;
        }
    }
}

int main() {
    int size;
    printf("Enter the size of the list: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'size' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &size);

    int arr[MAX_SIZE];
    printf("Enter the elements of the list: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    getFrequency(arr, size);

    return 0;
}