#include <stdio.h>

void findDifference(int list[], int size) {
    for (int i = 0; i < size - 1; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'list[i+1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        int difference = list[i + 1] - list[i];
        /* Possible weaknesses found:
         *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'list[i+1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        printf("Difference between %d and %d is %d\n", list[i + 1], list[i], difference);
    }
}

int main() {
    int size = 5;
    int list[] = {1, 2, 4, 7, 11};
    
    findDifference(list, size);
    
    return 0;
}