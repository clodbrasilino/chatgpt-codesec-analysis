#include <stdio.h>

void multiplyTuples(int tuple1[], int tuple2[], int size)
{
    int result[size];
    
    for (int i = 0; i < size; i++) {
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