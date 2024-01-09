#include <stdio.h>

void findEvenNumbers(int *list, int size) {
    printf("Even numbers in the mixed list: ");
    
    for (int i = 0; i < size; i++) {
        if (list[i] % 2 == 0) {
            printf("%d ", list[i]);
        }
    }
}

int main() {
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(list) / sizeof(list[0]);
    
    findEvenNumbers(list, size);
    
    return 0;
}