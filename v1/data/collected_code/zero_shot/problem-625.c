#include<stdio.h>

void interchangeFirstAndLast(int list[], int size) {
    if (size <= 1) {
        return;
    }
    
    int temp = list[0];
    list[0] = list[size-1];
    list[size-1] = temp;
}

int main() {
    int list[] = {1, 2, 3, 4, 5};
    int size = sizeof(list) / sizeof(list[0]);
    
    interchangeFirstAndLast(list, size);
    
    for (int i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
    
    return 0;
}