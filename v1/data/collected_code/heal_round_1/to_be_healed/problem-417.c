#include <stdio.h>

int findCommonElement(int arr[][2], int n) {
    /* Possible weaknesses found:
     *  Cannot determine that 'arr[0][0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int common = arr[0][0];
    int count;
    
    for (int i = 0; i < n; i++) {
        count = 0;
        
        for (int j = 0; j < n; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[j][0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'arr[i][0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (arr[i][0] == arr[j][0]) {
                count++;
            }
        }
        
        if (count == n) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i][0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            common = arr[i][0];
            break;
        }
    }
    
    return common;
}

int main() {
    int arr[][2] = {{1, 10}, {2, 20}, {3, 30}, {1, 40}};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int common = findCommonElement(arr, n);
    
    printf("The common first element is: %d", common);
    
    return 0;
}