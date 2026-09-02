#include <stdio.h>
#include <stdlib.h>

void find_divisible(const int *list, int size, int m, int n) {
    if (list == NULL || size <= 0 || m == 0 || n == 0) {
        return;
    }
    
    for (int i = 0; i < size; i++) {
        if (list[i] % m == 0 || list[i] % n == 0) {
            printf("%d ", list[i]);
        }
    }
    printf("\n");
}

int main(void) {
    int numbers[] = {10, 15, 20, 25, 30, 35, 40, 45, 50};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    find_divisible(numbers, size, 3, 5);
    
    return 0;
}