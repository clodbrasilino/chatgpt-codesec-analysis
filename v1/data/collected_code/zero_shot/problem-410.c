#include <stdio.h>

void* findMin(void* list[], int size) {
    if (size <= 0) {
        return NULL;
    }
    
    void* min = list[0];
    
    for (int i = 1; i < size; i++) {
        if (*(int*)list[i] < *(int*)min) {
            min = list[i];
        }
    }
    
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