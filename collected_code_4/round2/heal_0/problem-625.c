#include <stdio.h>

void swap_first_last(int *list, int n) {
    if (list == NULL || n < 1) {
        return;
    }

    int temp = list[0];
    list[0] = list[n-1];
    list[n-1] = temp;
}

int main() {
    int array[] = {1, 2, 3, 4, 5};
    int size = sizeof(array) / sizeof(array[0]);
    
    swap_first_last(array, size);
    
    for(int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }

    return 0;
}