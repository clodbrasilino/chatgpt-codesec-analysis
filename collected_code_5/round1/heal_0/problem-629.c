#include <stdio.h>

void find_even_numbers(int *numbers, int size) {
    if (numbers == NULL) {
        return;
    }
    
    for(int i=0; i<size; i++) {
        if (numbers[i] % 2 == 0) {
            printf("%d ", numbers[i]);
        }
    }
    printf("\n");
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    find_even_numbers(numbers, size);
    
    return 0;
}