#include <stdio.h>

void findMissingRanges(int list[], int size, int startRange, int endRange) {
    int i, j;
    int isMissingRange;
    
    printf("Missing Ranges: ");
    
    // Check if the starting range is missing
    /* Possible weaknesses found:
     *  Cannot determine that 'list[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    if (list[0] > startRange) {
        /* Possible weaknesses found:
         *  Cannot determine that 'list[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        printf("%d-%d ", startRange, list[0] - 1);
    }
    
    // Check for missing ranges between elements
    for (i = 1; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'list[i-1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (list[i] - list[i-1] > 1) {
            /* Possible weaknesses found:
             *  Cannot determine that 'list[i-1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            printf("%d-%d ", list[i-1] + 1, list[i] - 1);
        }
    }
    
    // Check if the ending range is missing
    /* Possible weaknesses found:
     *  Cannot determine that 'list[size-1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    if (endRange > list[size-1]) {
        /* Possible weaknesses found:
         *  Cannot determine that 'list[size-1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        printf("%d-%d ", list[size-1] + 1, endRange);
    }
    
    printf("\n");
}

int main() {
    int list[] = {4, 7, 10, 12, 15};
    int size = sizeof(list) / sizeof(list[0]);
    int startRange = 1;
    int endRange = 20;
    
    findMissingRanges(list, size, startRange, endRange);
    
    return 0;
}