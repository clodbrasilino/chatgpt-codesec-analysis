#include <stdio.h>

int isConsecutive(int list[], int size) {
    for (int i = 1; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'list[i-1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (list[i] != list[i-1] + 1) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int list1[] = {1, 2, 3, 4, 5}; // Consecutive
    int list2[] = {1, 3, 5, 7, 9}; // Not consecutive

    if (isConsecutive(list1, sizeof(list1)/sizeof(list1[0]))) {
        printf("list1 is consecutive.\n");
    }
    else {
        printf("list1 is not consecutive.\n");
    }
    
    if (isConsecutive(list2, sizeof(list2)/sizeof(list2[0]))) {
        printf("list2 is consecutive.\n");
    }
    else {
        printf("list2 is not consecutive.\n");
    }

    return 0;
}