#include <stdio.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'arr1' can be declared as const array [constParameter]
 *  Parameter 'arr2' can be declared as const array [constParameter]
 */
bool isSubset(int arr1[], int arr2[], int m, int n) {
    if (m < n) {
        return false;
    }

    /* Possible weaknesses found:
     *  Variable 'j' is assigned a value that is never used. [unreadVariable]
     */
    int i = 0, j = 0;
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            if (arr2[i] == arr1[j]) {
                break;
            }
        }
        
        if (j == m) {
            return false;
        }
    }
    
    return true;
}

int main() {
    int arr1[] = {11, 1, 13, 21, 3, 7};
    int arr2[] = {11, 3, 7, 1};
    
    int m = sizeof(arr1) / sizeof(arr1[0]);
    int n = sizeof(arr2) / sizeof(arr2[0]);
    
    if (isSubset(arr1, arr2, m, n)) {
        printf("arr2 is a subset of arr1\n");
    } else {
        printf("arr2 is not a subset of arr1\n");
    }
    
    return 0;
}