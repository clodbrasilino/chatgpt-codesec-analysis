#include <stdio.h>

int find_first_odd(int* numbers, int size) {
    for(int i=0; i<size; i++) {
        if(numbers[i] % 2 != 0)
            return numbers[i];
    }
    return -1;
}

int main() {
    int numbers[] = {2, 4, 6, 8, 9, 12, 14, 15};

    int size_of_numbers = sizeof(numbers) / sizeof(numbers[0]); 

    int first_odd = find_first_odd(numbers, size_of_numbers);

    if(first_odd == -1) {
        printf("No odd numbers found\n");
    } else {
        printf("First Odd number is %d\n", first_odd);
    }

    return 0;
}