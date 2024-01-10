#include <stdio.h>

void findValuesGreaterThan(int* list, int size, int target) {
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (list[i] > target) {
            /* Possible weaknesses found:
             *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            printf("%d\n", list[i]);
        }
    }
}

int main() {
    int list[] = {1, 4, 7, 3, 9, 2};
    int size = sizeof(list) / sizeof(list[0]);
    int target = 4;
    
    findValuesGreaterThan(list, size, target);
    
    return 0;
}