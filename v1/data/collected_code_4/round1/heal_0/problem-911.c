#include <stdio.h>
#include <stdlib.h>

int cmp(const void* p, const void* q) {
    int a = *(const int*)p;
    int b = *(const int*)q;
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

long MaxProductThreeNumbers(int* array, int size) {
    qsort(array, size, sizeof(int), cmp);
    long prod1 = 1, prod2 = 1;
    for (int i=0; i<3; ++i) {
        prod1 *= array[i];
        prod2 *= array[size-i-1];
    }
    return prod1 > prod2 ? prod1 : prod2;
}

int main()
{  
    int array[] = {1, -10, -20, 30, -40, 50};  
    int size = sizeof(array) / sizeof(array[0]);
    printf("%ld\n", MaxProductThreeNumbers(array, size));  
    return 0;  
}