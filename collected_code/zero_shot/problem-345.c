#include <stdio.h>

void findDifference(int list[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int difference = list[i + 1] - list[i];
        printf("Difference between %d and %d is %d\n", list[i + 1], list[i], difference);
    }
}

int main() {
    int size = 5;
    int list[] = {1, 2, 4, 7, 11};
    
    findDifference(list, size);
    
    return 0;
}