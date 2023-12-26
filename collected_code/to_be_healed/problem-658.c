#include <stdio.h>

int findMaxOccurrences(int list[], int size) {
    int maxCount = 0;
    int maxItem = 0;
    
    for (int i = 0; i < size; i++) {
        int count = 0;
        
        for (int j = 0; j < size; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'list[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (list[j] == list[i]) {
                count++;
            }
        }
        
        if (count > maxCount) {
            maxCount = count;
            /* Possible weaknesses found:
             *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            maxItem = list[i];
        }
    }
    
    return maxItem;
}

int main() {
    int list[] = {1, 2, 3, 4, 2, 3, 2, 1, 5, 2, 3};
    int size = sizeof(list) / sizeof(list[0]);
    
    int itemWithMaxOccurrences = findMaxOccurrences(list, size);
    
    printf("Item with maximum occurrences: %d\n", itemWithMaxOccurrences);
    
    return 0;
}