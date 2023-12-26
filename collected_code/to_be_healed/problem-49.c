#include<stdio.h>

#define ROWS 3
#define COLS 3

void extract_elements(int arr[ROWS][COLS], int extract_value) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i][j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (arr[i][j] == extract_value) {
                /* Possible weaknesses found:
                 *  Cannot determine that 'arr[i][0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 */
                printf("%d ", arr[i][0]);
                break;
            }
        }
    }
}

int main() {
    int arr[ROWS][COLS] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    int extract_value = 2;
    
    extract_elements(arr, extract_value);
    
    return 0;
}