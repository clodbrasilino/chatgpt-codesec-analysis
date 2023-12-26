#include <stdio.h>

void removeDuplicates(int list[], int size) {
    int result[size];
    int j = 0;
    
    for (int i = 0; i < size; i++) {
        int isDuplicate = 0;
        
        for (int k = 0; k < j; k++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'result[k]' is initialized [premium-bughuntingUninit]
             *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (list[i] == result[k]) {
                isDuplicate = 1;
                break;
            }
        }
        
        if (!isDuplicate) {
            /* Possible weaknesses found:
             *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            result[j++] = list[i];
        }
    }
    
    printf("Updated list: ");
    for (int i = 0; i < j; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'result[i]' is initialized [premium-bughuntingUninit]
         */
        printf("%d ", result[i]);
    }
    printf("\n");
}

int main() {
    int list[] = {1, 2, 2, 3, 4, 4, 5, 6, 6, 6};
    int size = sizeof(list) / sizeof(list[0]);
    
    printf("Original list: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
    
    removeDuplicates(list, size);
    
    return 0;
}