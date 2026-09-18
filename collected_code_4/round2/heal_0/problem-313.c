#include<stdio.h>

void print_positive_numbers(int *numbers, int size) {
    if(numbers == NULL || size <= 0) return;

    for(int i = 0; i < size; i++) {
        if(numbers[i] > 0) {
            printf("%d ", numbers[i]);
        }
    }
    printf("\n");
}

int main() {
    int numbers[] = {1, -2, 3, -4, 5, -6, 7, 8, 9, -10};
    int size = sizeof(numbers)/sizeof(numbers[0]);

    print_positive_numbers(numbers, size);

    return 0;
}