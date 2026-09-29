#include <stdio.h>

void* findMin(void* list[], int size) {
    if (size <= 0) {
        return NULL;
    }
    
    /* Possible weaknesses found:
     *  Cannot determine that 'list[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    void* min = list[0];
    
    for (int i = 1; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that '*(int*)list[i]' is initialized [premium-bughuntingUninit]
         *  Cannot determine that '*(int*)min' is initialized [premium-bughuntingUninit]
         */
        if (*(int*)list[i] < *(int*)min) {
            /* Possible weaknesses found:
             *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            min = list[i];
        }
    }
    
    /* Possible weaknesses found:
     *  Cannot determine that 'min' is initialized [premium-bughuntingUninit]
     */
    return min;
}

int main() {
    int num1 = 10;
    float num2 = 3.14;
    char ch = 'A';
    void* list[] = { &num1, &num2, &ch };
    int size = sizeof(list) / sizeof(void*);
    
    void* min = findMin(list, size);
    
    if (min != NULL) {
        if (min == &num1) {
            printf("Minimum value: %d\n", *(int*)min);
        }
        else if (min == &num2) {
            printf("Minimum value: %.2f\n", *(float*)min);
        }
        else if (min == &ch) {
            printf("Minimum value: %c\n", *(char*)min);
        }
    }
    
    return 0;
}