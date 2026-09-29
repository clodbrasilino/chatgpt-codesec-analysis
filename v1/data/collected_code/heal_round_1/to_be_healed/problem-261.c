#include <stdio.h>

void divideTuple(int tuple1[], int tuple2[], int size) {
    for(int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'tuple2[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'tuple1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        printf("%d / %d = %.2f\n", tuple1[i], tuple2[i], (float)tuple1[i] / tuple2[i]);
    }
}

int main() {
    int tuple1[] = {10, 20, 30, 40};
    int tuple2[] = {2, 4, 5, 8};
    int size = sizeof(tuple1) / sizeof(tuple1[0]);
    
    divideTuple(tuple1, tuple2, size);
    
    return 0;
}