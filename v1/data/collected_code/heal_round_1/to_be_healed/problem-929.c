#include <stdio.h>

int countRepeatedItems(int arr[], int n) {
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        int current = arr[i];
        int found = 0;
        
        for (int j = 0; j < i; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (current == arr[j]) {
                found = 1;
                break;
            }
        }
        
        if (!found) {
            int repetitions = 1;
            
            for (int k = i + 1; k < n; k++) {
                /* Possible weaknesses found:
                 *  Cannot determine that 'arr[k]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 */
                if (current == arr[k]) {
                    repetitions++;
                }
            }
            
            if (repetitions > 1) {
                count++;
            }
        }
    }
    
    return count;
}

int main() {
    int tuple[] = {1, 2, 3, 4, 1, 2, 5, 6, 3, 4};
    int count = countRepeatedItems(tuple, 10);
    
    printf("Number of repeated items: %d\n", count);
    
    return 0;
}