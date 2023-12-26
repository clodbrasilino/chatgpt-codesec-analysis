#include <stdio.h>

int findElementCount(int* arr, int n, int record) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[i] == record) {
            break;
        }
        count++;
    }
    return count;
}

int main() {
    int tuple[] = {5, 2, 7, 3, 2, 9};
    int record = 3;
    int count = findElementCount(tuple, sizeof(tuple) / sizeof(tuple[0]), record);
    printf("Element count before record: %d\n", count);
    
    return 0;
}