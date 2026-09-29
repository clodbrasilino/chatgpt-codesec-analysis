#include <stdio.h>

void removeNegative(int list[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (list[i] >= 0) {
            list[count] = list[i];
            count++;
        }
    }
    for (int i = count; i < size; i++) {
        list[i] = 0;
    }
}

int main() {
    int list[] = {1, -2, 3, -4, 5, -6};
    int size = sizeof(list) / sizeof(list[0]);
    
    removeNegative(list, size);
    
    for (int i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
    
    return 0;
}