#include <stdio.h>

void multiplyTuples(int tuple1[], int tuple2[], int size)
{
    int result[size];
    
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'tuple2[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'tuple1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        result[i] = tuple1[i] * tuple2[i];
    }
    
    printf("Resultant tuple: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", result[i]);
    }
}

int main()
{
    int tuple1[] = {1, 2, 3};
    int tuple2[] = {4, 5, 6};
    int size = sizeof(tuple1) / sizeof(tuple1[0]);
    
    multiplyTuples(tuple1, tuple2, size);
    
    return 0;
}