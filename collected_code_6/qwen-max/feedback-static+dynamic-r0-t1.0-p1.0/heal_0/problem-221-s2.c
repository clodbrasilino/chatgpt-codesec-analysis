#include <stdio.h>
#include <stdbool.h>

int find_first_even(int *numbers, int count) {
    for (int i = 0; i < count; ++i) {
        if (numbers[i] % 2 == 0) {
            return numbers[i];
        }
    }
    return -1;
}

int main() {
    int numbers[] = {1, 3, 5, 8, 10, 12};
    int count = sizeof(numbers) / sizeof(numbers[0]);
    int result = find_first_even(numbers, count);
    if (result != -1) {
        printf("The first even number is: %d\n", result);
    } else {
        printf("No even number found.\n");
    }
    return 0;
}