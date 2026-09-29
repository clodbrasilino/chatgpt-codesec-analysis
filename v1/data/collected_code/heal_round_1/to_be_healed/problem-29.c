#include <stdio.h>

int findOddOccurrence(int arr[], int size) {
    int i, j, count;
    for (i = 0; i < size; i++) {
        count = 0;
        for (j = 0; j < size; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'arr[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (arr[i] == arr[j])
                count++;
        }
        if (count % 2 != 0)
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            return arr[i];
    }
    return -1;
}

int main() {
    int arr[] = {1, 2, 3, 2, 1, 3, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    int result = findOddOccurrence(arr, size);
    if (result != -1)
        printf("The element occurring odd number of times is %d\n", result);
    else
        printf("No element occurs odd number of times\n");
    return 0;
}