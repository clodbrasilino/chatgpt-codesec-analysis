#include <stdio.h>

int isElementPresent(int list[], int size, int element) {
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (list[i] == element) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int list[] = {1, 2, 3, 4, 5};
    int size = sizeof(list) / sizeof(list[0]);
    int element = 3;
    
    if (isElementPresent(list, size, element)) {
        printf("Element is present in the list\n");
    } else {
        printf("Element is not present in the list\n");
    }

    return 0;
}