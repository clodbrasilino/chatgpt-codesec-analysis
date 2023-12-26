#include <stdio.h>

void removeNegative(int list[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (list[i] >= 0) {
            /* Possible weaknesses found:
             *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            list[count] = list[i];
            count++;
        }
    }
    for (int i = count; i < size; i++) {
        list[i] = 0;
    }
}

int main() {
    int list[] = {1, -2, 3, -4, 5, -6};
    int size = sizeof(list) / sizeof(list[0]);
    
    removeNegative(list, size);
    
    for (int i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
    
    return 0;
}