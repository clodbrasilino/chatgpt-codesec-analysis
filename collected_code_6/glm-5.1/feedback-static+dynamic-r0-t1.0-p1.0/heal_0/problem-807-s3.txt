#include <stdio.h>
#include <stdlib.h>

int find_first_odd(const int *numbers, size_t count) {
    if (numbers == NULL || count == 0) {
        return -1;
    }
    for (size_t i = 0; i < count; i++) {
        if (numbers[i] % 2 != 0) {
            return numbers[i];
        }
    }
    return -1;
}

int main(void) {
    int numbers[] = {2, 4, 6, 9, 10, 12};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    int result = find_first_odd(numbers, count);
    printf("%d\n", result);
    return 0;
}