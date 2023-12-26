#include <stdio.h>

void add_k_to_tuple(int tuple[], int k, int size) {
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'tuple[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        tuple[i] += k;
    }
}

int main() {
    int tuple[] = {1, 2, 3, 4, 5};
    int k = 10;
    int size = sizeof(tuple) / sizeof(tuple[0]);

    add_k_to_tuple(tuple, k, size);

    for(int i=0; i<size; i++) {
        printf("%d ", tuple[i]);
    }

    return 0;
}