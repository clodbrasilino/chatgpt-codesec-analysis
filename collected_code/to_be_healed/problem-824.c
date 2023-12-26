#include <stdio.h>

void removeEvenNumbers(int *list, int size) {
    int i, j;
    j = 0;
    for (i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (list[i] % 2 != 0) {
            /* Possible weaknesses found:
             *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            list[j] = list[i];
            j++;
        }
    }
    for (i = j; i < size; i++) {
        list[i] = 0;
    }
}

int main() {
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(list) / sizeof(list[0]);

    removeEvenNumbers(list, size);

    for (int i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }

    return 0;
}