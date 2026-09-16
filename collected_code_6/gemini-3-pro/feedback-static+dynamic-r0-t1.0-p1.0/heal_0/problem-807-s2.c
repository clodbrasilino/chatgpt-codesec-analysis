#include <stdio.h>
#include <stdlib.h>

int find_first_odd(const int *numbers, size_t size, int *result) {
    if (numbers == NULL || result == NULL || size == 0) {
        return -1;
    }

    for (size_t i = 0; i < size; i++) {
        if (numbers[i] % 2 != 0) {
            *result = numbers[i];
            return 0;
        }
    }

    return 1;
}

int main(void) {
    int numbers[] = {2, 4, 6, 8, 9, 10, 11};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    int first_odd = 0;

    int status = find_first_odd(numbers, size, &first_odd);

    if (status == 0) {
        printf("%d\n", first_odd);
    } else if (status == 1) {
        printf("No odd number found\n");
    } else {
        printf("Invalid input\n");
    }

    return 0;
}